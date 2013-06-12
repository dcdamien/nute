#pragma once

typedef void (BUTTON_HANDLER)(ubyte_t button);
void RegisterButtonHandlers(BUTTON_HANDLER ClickButtonHandler,BUTTON_HANDLER HoldButtonHandler);

extern BUTTON_HANDLER* gClickButtonHandler;
extern BUTTON_HANDLER* gHoldButtonHandler;

//draw pixel alpha channel support in MiddleWare

/*
TODO
��� ����� ��������� � ����������� ������.
���� �1 - �������� �������� ������� (������� ������, �������� ������, ������ �� �����).
���� �2 - ����������� ������� � ���������� �������� �������� (������������ ���������, ���� ������ �������������, ��������� �����).
���� �3 - ������� ����: ������� ���� � SD, ��������� ������ (��� �������� ��������, �������� ������� � �����, ��������� �������� �������), �������� ���� �� SD, ������� �������� ������� ��� ���������.
*/
