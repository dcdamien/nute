﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using NetworkLevel.NetworkDeliveryLevel;
using NetworkLevel.WCFServices;
using PillInterfaces;

namespace HonorLogic
{
    public sealed class GlobalModel : IGlobalModel
    {
        private readonly ArmletStorage _armletStorage = new ArmletStorage();
        private readonly ArmletList _armletList = new ArmletList();
        private readonly IArmletDeliveryServece _armletService;
        private readonly IGateDeliveryService _gateService;
        private readonly Lazy<GateModel>[] _gates;

        private readonly Timer _timer;

        
        public GlobalModel(IArmletDeliveryServece armletService, IGateDeliveryService gateService)
        {
            _armletService = armletService;
            _gateService = gateService;

            _gates = new Lazy<GateModel>[Byte.MaxValue + 1];
            for (var gateIndex = 0; gateIndex <= Byte.MaxValue; gateIndex++)
            {
                var index = (byte) gateIndex; //To prevent closure problems. C# 5.0 will fix it
                _gates[gateIndex] = new Lazy<GateModel>(() => new GateModel(gateService, index));
            }

            for (var armletIndex = 1; armletIndex <= 120; armletIndex++)
            {
                _armletList.CreateIfNeeded((byte) armletIndex, CreateArmlet);
            }
            
            
            _armletService.ArmletsStatusUpdate +=ArmletServiceArmletsStatusUpdate;
            _gateService.GateConnected += OnNewGateOnline;
            _armletService.ArmletSuccess += OnArmletListSuccess;
            _armletService.ArmletSendsData += _armletService_ArmletSendsData;

            _timer = new Timer(SendHeartBeat, 0, 0, 1 * 1000);
        }

        private static void SendHeartBeat(object state)
        {
            var gates = GateConnectionPool.GateConnections.Values.ToArray(); // TODO FIXME possible not thread-safe
            foreach (var gate in gates)
            {
                try
                {
                    gate.SendHeartbeat();
                }
                catch (Exception)
                {
                    
                }
                
            }
        }

        void _armletService_ArmletSendsData(byte armletId, byte[] payload)
        {
            if (payload.Length > 3)
            {
                _armletList.GetById(armletId).SetToxic(payload[3]);
            }
        }

        private void OnArmletListSuccess(byte armletId)
        {
            _armletList.GetById(armletId).SetStatus("Сообщение доставлено");
            OnArmletListUpdated();
        }

        private void ArmletServiceArmletsStatusUpdate(PlayerUpdate[] obj)
        {
            foreach (var playerStatusUpdate in obj)
            {
                //_armletList.CreateIfNeeded(playerStatusUpdate.ArmletID, CreateArmlet);
                _armletList.UpdateArmlet(playerStatusUpdate);
            }

            OnArmletListUpdated();
        }

        private Armlet CreateArmlet(byte armletId)
        {
            return new Armlet(armletId, this, _armletStorage.GetName(armletId), _armletStorage.GetRegen(armletId));
        }
        
        public IEnumerable<IArmletInfo> GetArmlets()
        {
            return _armletList.Get();
        }

        public event Action ArmletListUpdated;
        public event Action<byte> NewGateOnline;

        public void SendMessageToAll(string text)
        {
            SendPayloadToAll(CreateMessagePayload(text));
        }

        private static byte[] CreateMessagePayload(string text)
        {
            if (text.Length > 120)
            {
                throw new Exception("Message too long");
            }
            return CreateStringPayload(MessageId.MSG_SHOW_MESSAGE, string.Format("* {0}: {1}\n\n", DateTime.Now.ToShortTimeString(), text));
        }

        private void OnNewGateOnline(byte obj)
        {
            var handler = NewGateOnline;
            if (handler != null) handler(obj);
        }

        public IGateModel GetGateModel(byte gateId)
        {
            return _gates[gateId].Value;
        }

        private void OnArmletListUpdated()
        {
            var handler = ArmletListUpdated;
            if (handler != null) handler();
        }

        private void SendPayload(IArmletInfo armlet, byte[] payload)
        {
            armlet.SetStatus("Отправляется сообщение");
            OnArmletListUpdated();
            _armletService.DeliverToSingleArmlet(armlet.Id, payload);
        }

        private void SendPayloadToAll(byte[] payload)
        {
            var armlets = _armletList.GetAll();
            foreach (var armletInfo in armlets)
            {
                armletInfo.SetStatus("Отправляется сообщение");
            }
            OnArmletListUpdated();
            _armletService.DeliverToArmlets(armlets.Select(armlet => armlet.Id).ToArray(), payload);
        }

        public void SavePersistent()
        {
            Task.Factory.StartNew(() => _armletStorage.SaveData(_armletList.GetDataToStore()));
        }

        private static byte[] CreatePayload(MessageId messageId, IEnumerable<byte> data)
        {
            return new[] {(byte) messageId, (byte) 0x00, (byte) 0x00}.Concat(data).ToArray();
        }

        private static byte[] CreateStringPayload(MessageId messageId, string text)
        {
            return CreatePayload(messageId, Encoding.GetEncoding(1251).GetBytes(text).Concat(new byte[]{0}).ToArray());
        }

        private void SendCommand(IArmletInfo armletId, MessageId messageId, string text)
        {
            if (text.Length > 140)
            {
                throw new ArgumentOutOfRangeException("text");
            }
            SendPayload(armletId, CreateStringPayload(messageId, text));
        }

        public void SendSetName(string text, IArmletInfo armletId)
        {
            text = Armlet.TransformName(text);
            armletId.SetName(text);
            SendCommand(armletId, MessageId.MSG_SET_PLAYER_NAME, text);
        }

        public void SendShowMessage(IArmletInfo armletId, string text)
        {
            SendPayload(armletId, CreateMessagePayload(text));
        }

        public void SetSetPlayerRegen(IArmletInfo armlet, byte regen)
        {
            armlet.SetRegen(regen);
            SendPayload(armlet, CreatePayload(MessageId.MSG_SET_PLAYER_REGENERATION, new[] {regen}));
        }

        public void SendSetLockList(IArmletInfo armlet, byte[] lockList)
        {
            SendPayload(armlet, CreatePayload(MessageId.MSG_UPDATE_LOCK_LIST, lockList));
        }

        public void SendRoomHit(byte roomId)
        {
            SendPayloadToAll(CreatePayload(MessageId.MSG_ROOM_HIT, new[] {roomId}));
        }

        public void UpdateAllNames()
        {
            foreach (var armletInfo in _armletList.GetAll())
            {
                SendCommand(armletInfo, MessageId.MSG_SET_PLAYER_NAME, armletInfo.Name);
                SendPayload(armletInfo, CreatePayload(MessageId.MSG_SET_PLAYER_REGENERATION, new[] { armletInfo.Regen }));
            }
        }
    }
}