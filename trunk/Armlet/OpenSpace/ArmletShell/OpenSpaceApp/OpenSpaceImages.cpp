#include "ArmletShell.h"
#include "ThreeKShell.h"
#include "OpenSpaceImages.h"

#pragma region static img defs

const Color battery_stubBitmap[]={
	0x0FD3, 0xFAB2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xFAA2, 0xF9A2, 0xFBB2, 0xFFD3, 
	0xFDC2, 0xF470, 0xF891, 0xF791, 0xF791, 0xF791, 0xF891, 0xF891, 0xF791, 0xF791, 0xF791, 0xF891, 0xF8A1, 0xF791, 0xF791, 0xF791, 0xF891, 0xF8A1, 0xF791, 0xF791, 0xF791, 0xF891, 0xF8A1, 0xF480, 0xFFD3, 
	0xFCB2, 0xF791, 0xF791, 0xF260, 0xF270, 0xF260, 0xFAB2, 0xFAA2, 0xF260, 0xF370, 0xF260, 0xFAA2, 0xFCB2, 0xF260, 0xF370, 0xF260, 0xF8A1, 0xFCB2, 0xF581, 0xF791, 0xF691, 0xF691, 0xFFD3, 0xF691, 0xFED3, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A1, 0xF8A1, 0xF050, 0xF060, 0xF050, 0xF891, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF691, 0xFAA2, 0xF8A1, 0xFFE3, 0x0FD3, 0xF681, 0xFEC3, 0xF581, 0xFEC3, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF8A1, 0xFFD3, 0xFEC3, 0xF691, 0xFFD3, 0xF581, 0xF581, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF8A1, 0xFFD3, 0xFED3, 0xF691, 0xFEC3, 0xFFD3, 0xF581, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF8A1, 0xFFD3, 0xFED3, 0xF691, 0xFEC3, 0xFFD3, 0xF681, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF8A1, 0xFFD3, 0xFFD3, 0xF691, 0xFEC3, 0xFFD3, 0xF581, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF8A1, 0xFFD3, 0xFEC3, 0xF691, 0xFFD3, 0xF791, 0xF480, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A1, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFAB2, 0xF9A1, 0xFFE3, 0xFFD3, 0xF691, 0xFEC3, 0xF581, 0xFDC2, 
	0xFCB2, 0xF791, 0xF581, 0xF050, 0xF060, 0xF050, 0xF9A2, 0xF9A1, 0xF050, 0xF060, 0xF050, 0xF8A1, 0xFBB2, 0xF050, 0xF060, 0xF050, 0xF791, 0xFBB2, 0xF581, 0xF9A2, 0xF8A1, 0xF581, 0xFFD3, 0xF691, 0x0FD3, 
	0xFCB2, 0xF581, 0xF8A1, 0xF581, 0xF691, 0xF681, 0xFAA2, 0xF9A2, 0xF581, 0xF691, 0xF581, 0xF9A2, 0xFAA2, 0xF581, 0xF691, 0xF681, 0xF8A1, 0xFBB2, 0xF791, 0xF791, 0xF791, 0xF8A1, 0xFCB2, 0xF480, 0xFEC3, 
	0xFEC3, 0xF691, 0xF791, 0xF891, 0xF891, 0xF891, 0xF791, 0xF791, 0xF891, 0xF891, 0xF891, 0xF791, 0xF791, 0xF891, 0xF891, 0xF891, 0xF791, 0xF791, 0xF791, 0xF791, 0xF891, 0xF791, 0xF691, 0xF891, 0xFFD3 
};
const Color menu_downBitmap[]={
	0x0CCC, 0xFCCC, 0x0CCC, 0xFCCC, 0x0CCC, 0xFCCC, 0x0CCC, 0x0CCC, 0xFCCC, 
	0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 0xFBBB, 
	0xFBBB, 0xF888, 0xF111, 0xF222, 0xF222, 0xF222, 0xF111, 0xF555, 0xFBBB, 
	0xFAAA, 0xFAAA, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF888, 0xFAAA, 
	0xFAAA, 0xFAAA, 0xF888, 0xF000, 0xF000, 0xF000, 0xF555, 0xFAAA, 0xFAAA, 
	0xF999, 0xF999, 0xFAAA, 0xF444, 0xF000, 0xF111, 0xF999, 0xF999, 0xF999, 
	0xF999, 0xF999, 0xF999, 0xF888, 0xF000, 0xF555, 0xFAAA, 0xF999, 0xF999, 
	0xF888, 0xF888, 0xF888, 0xF999, 0xF666, 0xF888, 0xF888, 0xF888, 0xF888, 
	0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888 
};
const Color menu_leftBitmap[]={
	0x0888, 0xF888, 0xF999, 0xF999, 0xFAAA, 0xFAAA, 0xFBBB, 0xFBBB, 0xFCCC, 
	0xF888, 0xF888, 0xF999, 0xF999, 0xFAAA, 0xFAAA, 0xF888, 0xFBBB, 0xFCCC, 
	0x0888, 0xF888, 0xF999, 0xFAAA, 0x0888, 0xF222, 0xF111, 0xFBBB, 0xFCCC, 
	0xF888, 0xF999, 0xF888, 0xF444, 0xF000, 0xF000, 0xF222, 0xFBBB, 0xFCCC, 
	0xF888, 0xF666, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xFBBB, 0xFCCC, 
	0x0888, 0xF888, 0xF555, 0xF111, 0xF000, 0xF000, 0xF222, 0xFBBB, 0xFCCC, 
	0xF888, 0xF888, 0xFAAA, 0xF999, 0xF555, 0xF000, 0xF111, 0xFBBB, 0xFCCC, 
	0x0888, 0xF888, 0xF999, 0xF999, 0xFAAA, 0xF888, 0xF555, 0xFBBB, 0xFCCC, 
	0x0888, 0xF888, 0xF999, 0xF999, 0xFAAA, 0xFAAA, 0xFBBB, 0xFBBB, 0xFCCC 
};
const Color menu_rightBitmap[]={
	0x0CCC, 0xFBBB, 0xFBBB, 0xFAAA, 0xFAAA, 0xF999, 0xF999, 0xF888, 0xF888, 
	0xFCCC, 0xFBBB, 0xF888, 0xFAAA, 0xFAAA, 0xF999, 0xF999, 0xF888, 0xF888, 
	0x0CCC, 0xFBBB, 0xF111, 0xF222, 0xF888, 0xFAAA, 0xF999, 0xF888, 0xF888, 
	0xFCCC, 0xFBBB, 0xF222, 0xF000, 0xF000, 0xF444, 0xF888, 0xF999, 0xF888, 
	0x0CCC, 0xFBBB, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF666, 0xF888, 
	0xFCCC, 0xFBBB, 0xF222, 0xF000, 0xF000, 0xF111, 0xF555, 0xF888, 0xF888, 
	0x0CCC, 0xFBBB, 0xF111, 0xF000, 0xF555, 0xF999, 0xFAAA, 0xF888, 0xF888, 
	0x0CCC, 0xFBBB, 0xF555, 0xF888, 0xFAAA, 0xF999, 0xF999, 0xF888, 0xF888, 
	0xFCCC, 0xFBBB, 0xFBBB, 0xFAAA, 0xFAAA, 0xF999, 0xF999, 0xF888, 0xF888 
};
const Color net_stubBitmap[]={
	0x0FD3, 0xFFD3, 0xFDC2, 0xFDC2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF160, 0xF160, 0xFEC3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF050, 0xFEC2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFEC3, 0xFCB2, 0xF470, 0xF891, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFFD3, 0xF9A1, 0xF040, 0xF480, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFFD3, 0xFAA2, 0xF050, 0xF581, 0xFFD3, 0xFAA2, 0xFAA2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFFD3, 0xFAA2, 0xF050, 0xF581, 0xFFD3, 0xF050, 0xF050, 0xFDC2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFFD3, 0xFAA2, 0xF050, 0xF581, 0xFFD3, 0xF060, 0xF060, 0xFDC2, 0xFED3, 0xFDC2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC2, 0xF060, 0xF060, 0xFFD3, 0xFAA2, 0xF050, 0xF581, 0xFFD3, 0xF060, 0xF060, 0xFEC3, 0xF791, 0xF050, 0xF8A1, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFDC2, 0xF060, 0xF050, 0xFFD3, 0xF9A1, 0xF040, 0xF480, 0xFFD3, 0xF050, 0xF050, 0xFEC3, 0xF581, 0xF040, 0xF791, 0xFFE3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFEC3, 0xF581, 0xF481, 0xFFD3, 0xFBB2, 0xF470, 0xF8A1, 0xFFD3, 0xF581, 0xF481, 0xFEC3, 0xF9A1, 0xF470, 0xFAB2, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 
	0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3, 0xFFD3 
};
const Color scroll_downBitmap[]={
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF777, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF555, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF444, 0xF444, 0xF666, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF555, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xFAAA, 0xFAAA, 0xFAAA, 0xFAAA, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xF222, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xF222, 0xF222, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xFCCC, 0xFFFF, 0xFFFF, 0xF999, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF666, 0xFFFF, 0xFFFF, 0xFEEE, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFEEE, 0xFFFF, 0xFFFF, 0xF666, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF333, 0xFFFF, 0xFFFF, 0xFFFF, 0xF333, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF333, 0xFFFF, 0xFFFF, 0xFFFF, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFEEE, 0xFFFF, 0xFFFF, 0xF555, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF555, 0xFFFF, 0xFFFF, 0xFEEE, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xFCCC, 0xFFFF, 0xFFFF, 0xF888, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF888, 0xFFFF, 0xFFFF, 0xFCCC, 0xF000, 0xF000, 0xF000, 0xFAAA, 0xFFFF, 0xFFFF, 0xFBBB, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xFBBB, 0xFFFF, 0xFFFF, 0xFAAA, 0xF000, 0xF777, 0xFFFF, 0xFFFF, 0xFDDD, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFDDD, 0xFFFF, 0xFFFF, 0xFAAA, 0xFFFF, 0xFFFF, 0xFFFF, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0xFFFF, 0xFFFF, 0xFFFF, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF666, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF777, 0xFFFF, 0xFAAA, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF555, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF222, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF95A 
};
const Color scroll_upBitmap[]={
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF95A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF222, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF555, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF666, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF777, 0xFFFF, 0xFAAA, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0xFFFF, 0xFFFF, 0xFFFF, 0xF777, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xF444, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFDDD, 0xFFFF, 0xFFFF, 0xFAAA, 0xFFFF, 0xFFFF, 0xFFFF, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xFBBB, 0xFFFF, 0xFFFF, 0xFAAA, 0xF000, 0xF777, 0xFFFF, 0xFFFF, 0xFDDD, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF888, 0xFFFF, 0xFFFF, 0xFCCC, 0xF000, 0xF000, 0xF000, 0xFAAA, 0xFFFF, 0xFFFF, 0xFBBB, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF555, 0xFFFF, 0xFFFF, 0xFEEE, 0xF111, 0xF000, 0xF000, 0xF000, 0xF000, 0xFCCC, 0xFFFF, 0xFFFF, 0xF888, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF333, 0xFFFF, 0xFFFF, 0xFFFF, 0xF333, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFEEE, 0xFFFF, 0xFFFF, 0xF555, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF111, 0xFEEE, 0xFFFF, 0xFFFF, 0xF666, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF333, 0xFFFF, 0xFFFF, 0xFFFF, 0xF333, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xFCCC, 0xFFFF, 0xFFFF, 0xF999, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF666, 0xFFFF, 0xFFFF, 0xFEEE, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xF222, 0xF222, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF222, 0xF222, 0xF222, 0xF111, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xFAAA, 0xFAAA, 0xFAAA, 0xFAAA, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF999, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF111, 0xF555, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF555, 0xF444, 0xF444, 0xF666, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF222, 0xF555, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF000, 0xF444, 0x0A4A, 
	0x0A4A, 0x0A4A, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF888, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF777, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF666, 0xF777, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 
	0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A, 0x0A4A 
};
#pragma endregion

BitmapImage _app_def_images[6];

void FillAppSpecificImages(ImagesRepository* images)
{

	//battery_stub
	_app_def_images[0].ImageSize.Height = 13;
	_app_def_images[0].ImageSize.Width  = 25;
	_app_def_images[0].Bitmap = (Color*) battery_stubBitmap;
	images->RegisterImage(&_app_def_images[0]);

	//menu_down
	_app_def_images[1].ImageSize.Height = 9;
	_app_def_images[1].ImageSize.Width  = 9;
	_app_def_images[1].Bitmap = (Color*) menu_downBitmap;
	images->RegisterImage(&_app_def_images[1]);

	//menu_left
	_app_def_images[2].ImageSize.Height = 9;
	_app_def_images[2].ImageSize.Width  = 9;
	_app_def_images[2].Bitmap = (Color*) menu_leftBitmap;
	images->RegisterImage(&_app_def_images[2]);

	//menu_right
	_app_def_images[3].ImageSize.Height = 9;
	_app_def_images[3].ImageSize.Width  = 9;
	_app_def_images[3].Bitmap = (Color*) menu_rightBitmap;
	images->RegisterImage(&_app_def_images[3]);

	//net_stub
	_app_def_images[4].ImageSize.Height = 12;
	_app_def_images[4].ImageSize.Width  = 19;
	_app_def_images[4].Bitmap = (Color*) net_stubBitmap;
	images->RegisterImage(&_app_def_images[4]);

	//scroll_down
	_app_def_images[5].ImageSize.Height = 57;
	_app_def_images[5].ImageSize.Width  = 28;
	_app_def_images[5].Bitmap = (Color*) scroll_downBitmap;
	images->RegisterImage(&_app_def_images[5]);

	//scroll_up
	_app_def_images[6].ImageSize.Height = 57;
	_app_def_images[6].ImageSize.Width  = 28;
	_app_def_images[6].Bitmap = (Color*) scroll_upBitmap;
	images->RegisterImage(&_app_def_images[6]);

}


