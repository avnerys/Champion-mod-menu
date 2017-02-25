#include "stdafx.h"

float menux = 0.2f;
rgba titleText = { 0, 0, 0, 255 };
rgba titleRect = { 255, 200, 0, 255 };
rgba scroller = { 80, 80, 80, 200 };
rgba options = { 0, 0, 0, 255 };
rgba optionsrect = { 255, 220, 30, 60 };

int optioncount;
int currentoption;
bool optionpress = false;
bool leftpress = false;
bool rightpress = false;
bool uppress = false;
bool downpress = false;
bool opened = false;

char* currentmenu[200];
char* actualmenu = "main";
int lastoption[200];
int menulevel = 0;
int infocount;
int Delay = GetTickCount();

int Menu::getKeyPressed(int key) {
	return GetAsyncKeyState(key);
}

char* Menu::StringToChar(std::string string) {
	return _strdup(string.c_str());
}

bool Menu::currentMenu(char* menuname) {
	if (menuname == actualmenu) return true;
	else return false;
}

bool Menu::open() {
	return opened;
}

void Menu::changeMenu(char* menuname) {
	currentmenu[menulevel] = actualmenu;
	lastoption[menulevel] = currentoption;
	menulevel++;
	actualmenu = menuname;
	currentoption = 1;
}

void Menu::backMenu() {
	menulevel--;
	actualmenu = currentmenu[menulevel];
	currentoption = lastoption[menulevel];
}

void Menu::drawText(char* text, int font, float x, float y, float scalex, float scaley, rgba rgba, bool center) {
	UI::SET_TEXT_FONT(font);
	UI::SET_TEXT_SCALE(scalex, scaley);
	UI::SET_TEXT_COLOUR(rgba.r, rgba.g, rgba.b, rgba.a);
	UI::SET_TEXT_CENTRE(center);
	UI::_SET_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(text);
	UI::_DRAW_TEXT(x, y);
};

void Menu::drawNotification(char* msg) {
	UI::_SET_NOTIFICATION_TEXT_ENTRY("STRING");
	UI::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(msg);
	UI::_DRAW_NOTIFICATION(false, 1);
};

void Menu::drawRect(float x, float y, float width, float height, rgba rgba) {
	GRAPHICS::DRAW_RECT(x, y, width, height, rgba.r, rgba.g, rgba.b, rgba.a);
};

void Menu::drawSprite(char* Streamedtexture, char* textureName, float x, float y, float width, float height, float rotation, rgba rgba)
{
	if (!GRAPHICS::HAS_STREAMED_TEXTURE_DICT_LOADED(Streamedtexture)) GRAPHICS::REQUEST_STREAMED_TEXTURE_DICT(Streamedtexture, false);
	else GRAPHICS::DRAW_SPRITE(Streamedtexture, textureName, x, y, width, height, rotation, rgba.r, rgba.g, rgba.b, rgba.a);
};

void Menu::Title(char* title) {
	optioncount = 0;
	drawText(title, 7, menux, 0.095f, 0.85f, 0.85f, titleText, true);
	drawRect(menux, 0.1175f, 0.23f, 0.085f, titleRect);
};

bool Menu::skinOption(char* option, char* nameID, char* *skin) {
	Option(option);

	if (optionpress && currentoption == optioncount) {
		*skin = nameID;
		return true;
	}
	else return false;
}

bool Menu::Option(char* option) {
	optioncount++;

	bool thisOption = false;
	if (currentoption == optioncount) thisOption = true;

	if (currentoption <= 16 && optioncount <= 16)
	{
		drawText(option, 6, menux - 0.1f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, false);
		drawRect(menux, ((optioncount * 0.035f) + 0.1415f), 0.23f, 0.035f, optionsrect);
		if (thisOption) drawRect(menux, ((optioncount * 0.035f) + 0.1415f), 0.23f, 0.035f, scroller);
	}

	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
	{
		drawText(option, 6, menux - 0.1f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, false);
		drawRect(menux, ((optioncount - (currentoption - 16)) * 0.035f + 0.1415f), 0.23f, 0.035f, optionsrect);
		if (thisOption) drawRect(menux, ((optioncount - (currentoption - 16)) * 0.035f + 0.1415f), 0.23f, 0.035f, scroller);
	}

	if (optionpress && currentoption == optioncount) return true;
	else return false;
};

bool Menu::MenuOption(char* option, char* menu) {
	Option(option);

	if (currentoption <= 16 && optioncount <= 16)
		drawText(">>", 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(">>", 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (optionpress && currentoption == optioncount) {
		optionpress = false;
		changeMenu(menu);
		return true;
	}
	else return false;
}

bool Menu::IntOption(char* option, int *var, int min, int max, int step) {
	Option(option);

	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + std::to_string(*var) + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + std::to_string(*var) + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*var <= min) *var = max;
			else *var -= step;
			leftpress = false;
			return true;
		}
		if (*var < min) *var = max;
		if (rightpress) {
			if (*var >= max) *var = min;
			else *var += step;
			rightpress = false;
			return true;
		}
		if (*var > max) *var = min;
	}

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

bool Menu::FloatOption(char* option, float *var, float min, float max, float step) {
	Option(option);



	char buf[100];
	_snprintf_s(buf, sizeof(buf), "%.2f", *var);

	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + (std::string)buf + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + (std::string)buf + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*var <= min) *var = max;
			else *var -= step;
			leftpress = false;
			return true;
		}
		if (*var < min) *var = max;

		if (rightpress) {
			if (*var >= max) *var = min;
			else *var += step;
			rightpress = false;
			return true;
		}
		if (*var > max) *var = min;
	}

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

bool Menu::BoolOption(char* option, bool *b00l) {
	Option(option);
	if (currentoption <= 16 && optioncount <= 16)
		drawSprite("commonmenu", *b00l ? "shop_box_tick" : "shop_box_blank",
			menux + 0.068f, (optioncount * 0.035f + 0.141f), 0.03f, 0.05f, 0, options);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawSprite("commonmenu", *b00l ? "shop_box_tick" : "shop_box_blank",
			menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, options);
	if (optionpress && currentoption == optioncount) {
		*b00l ^= 1;
		return true;
	}
	else return false;
}

bool Menu::BoolSpriteOption(char* option, bool b00l, char* category, char* spriteOn, char* spriteOff) {
	Option(option);

	if (currentoption <= 16 && optioncount <= 16)
		drawSprite(category, b00l ? spriteOn : spriteOff,
			menux + 0.068f, (optioncount * 0.035f + 0.141f), 0.03f, 0.05f, 0, options);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawSprite(category, b00l ? spriteOn : spriteOff,
			menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.141f), 0.03f, 0.05f, 0, options);

	if (optionpress && currentoption == optioncount) return true;
	else return false;
}

bool Menu::IntArray(char* option, int display[], int *PlaceHolderInt) {
	Option(option);

	int min = 0;
	int max = sizeof(display) / sizeof(*display);

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*PlaceHolderInt <= min) *PlaceHolderInt = max;
			else *PlaceHolderInt -= 1;
			leftpress = false;
			return true;
		}
		if (*PlaceHolderInt < min) *PlaceHolderInt = max;
		if (rightpress) {
			if (*PlaceHolderInt >= max) *PlaceHolderInt = min;
			else *PlaceHolderInt += 1;
			rightpress = false;
			return true;
		}
		if (*PlaceHolderInt > max) *PlaceHolderInt = min;
	}
	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + std::to_string(display[*PlaceHolderInt]) + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + std::to_string(display[*PlaceHolderInt]) + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

bool Menu::FloatArray(char* option, float display[], int *PlaceHolderInt) {
	Option(option);

	int min = 0;
	int max = sizeof(display) / sizeof(*display);

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*PlaceHolderInt <= min) *PlaceHolderInt = max;
			else *PlaceHolderInt -= 1;
			leftpress = false;
			return true;
		}
		if (*PlaceHolderInt < min) *PlaceHolderInt = max;
		if (rightpress) {
			if (*PlaceHolderInt >= max) *PlaceHolderInt = min;
			else *PlaceHolderInt += 1;
			rightpress = false;
			return true;
		}
		if (*PlaceHolderInt > max) *PlaceHolderInt = min;
	}

	char buf[30];
	_snprintf_s(buf, sizeof(buf), "%.2f", display[*PlaceHolderInt]);

	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + (std::string)buf + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + (std::string)buf + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

bool Menu::CharArray(char* option, LPCSTR display[], int *PlaceHolderInt, int arraylengh) {
	Option(option);

	int min = 0;
	int max = arraylengh;

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*PlaceHolderInt <= min) *PlaceHolderInt = max;
			else *PlaceHolderInt -= 1;
			leftpress = false;
		}
		if (*PlaceHolderInt < min) *PlaceHolderInt = max;
		if (rightpress) {
			if (*PlaceHolderInt >= max) *PlaceHolderInt = min;
			else *PlaceHolderInt += 1;
			rightpress = false;
		}
		if (*PlaceHolderInt > max) *PlaceHolderInt = min;
	}
	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + (std::string)display[*PlaceHolderInt] + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + (std::string)display[*PlaceHolderInt] + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

bool Menu::StringArray(char* option, std::string display[], int *PlaceHolderInt) {
	Option(option);

	int min = 0;
	int max = sizeof(display) / sizeof(*display) + 1;

	if (currentoption == optioncount) {
		if (leftpress) {
			if (*PlaceHolderInt <= min) *PlaceHolderInt = max;
			else *PlaceHolderInt -= 1;
			leftpress = false;
		}
		if (*PlaceHolderInt < min) *PlaceHolderInt = max;
		if (rightpress) {
			if (*PlaceHolderInt >= max) *PlaceHolderInt = min;
			else *PlaceHolderInt += 1;
			rightpress = false;
		}
		if (*PlaceHolderInt > max) *PlaceHolderInt = min;
	}
	if (currentoption <= 16 && optioncount <= 16)
		drawText(StringToChar("<" + display[*PlaceHolderInt] + ">"), 6, menux + 0.068f, (optioncount * 0.035f + 0.125f), 0.5f, 0.5f, options, true);
	else if ((optioncount > (currentoption - 16)) && optioncount <= currentoption)
		drawText(StringToChar("<" + display[*PlaceHolderInt] + ">"), 6, menux + 0.068f, ((optioncount - (currentoption - 16)) * 0.035f + 0.125f), 0.5f, 0.5f, options, true);

	if (optionpress && currentoption == optioncount)
		return true;
	else return false;
}

void Menu::TeleportOption(char* option, float x, float y, float z) {
	Option(option);
	if (currentoption == optioncount && optionpress) {
		Entity handle = PLAYER::PLAYER_PED_ID();
		if (PED::IS_PED_IN_ANY_VEHICLE(PLAYER::PLAYER_PED_ID(), false))
			handle = PED::GET_VEHICLE_PED_IS_USING(PLAYER::PLAYER_PED_ID());
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(handle, x, y, z, false, false, false);
	}
}

void Menu::IniWriteInt(LPCWSTR file, LPCWSTR section, LPCWSTR key, int value)
{
	wchar_t newValue[256];
	wsprintf(newValue, L"%d", value);
	WritePrivateProfileString(section, key, newValue, file);
}

int Menu::IniReadInt(LPCWSTR file, LPCWSTR section, LPCWSTR key)
{
	int returning = GetPrivateProfileInt(section, key, NULL, file);
	return returning;
}

void Menu::LoadMenuTheme(LPCWSTR file)
{
	// Title Text
	titleText.r = IniReadInt(file, L"Title Text", L"Red");
	titleText.g = IniReadInt(file, L"Title Text", L"Green");
	titleText.b = IniReadInt(file, L"Title Text", L"Blue");
	titleText.a = IniReadInt(file, L"Title Text", L"Alpha");

	// Title Rect
	titleRect.r = IniReadInt(file, L"Title Rect", L"Red");
	titleRect.g = IniReadInt(file, L"Title Rect", L"Green");
	titleRect.b = IniReadInt(file, L"Title Rect", L"Blue");
	titleRect.a = IniReadInt(file, L"Title Rect", L"Alpha");

	// Scroller
	scroller.r = IniReadInt(file, L"Scroller", L"Red");
	scroller.g = IniReadInt(file, L"Scroller", L"Green");
	scroller.b = IniReadInt(file, L"Scroller", L"Blue");
	scroller.a = IniReadInt(file, L"Scroller", L"Alpha");

	// Option Text
	options.r = IniReadInt(file, L"Options Text", L"Red");
	options.g = IniReadInt(file, L"Options Text", L"Green");
	options.b = IniReadInt(file, L"Options Text", L"Blue");
	options.a = IniReadInt(file, L"Options Text", L"Alpha");

	// Option Rect
	optionsrect.r = IniReadInt(file, L"Options Rect", L"Red");
	optionsrect.g = IniReadInt(file, L"Options Rect", L"Green");
	optionsrect.b = IniReadInt(file, L"Options Rect", L"Blue");
	optionsrect.a = IniReadInt(file, L"Options Rect", L"Alpha");
}

void Menu::SaveMenuTheme(LPCWSTR file)
{
	// Title Text
	IniWriteInt(file, L"Title Text", L"Red", titleText.r);
	IniWriteInt(file, L"Title Text", L"Green", titleText.g);
	IniWriteInt(file, L"Title Text", L"Blue", titleText.b);
	IniWriteInt(file, L"Title Text", L"Alpha", titleText.a);

	// Title Rect
	IniWriteInt(file, L"Title Rect", L"Red", titleRect.r);
	IniWriteInt(file, L"Title Rect", L"Green", titleRect.g);
	IniWriteInt(file, L"Title Rect", L"Blue", titleRect.b);
	IniWriteInt(file, L"Title Rect", L"Alpha", titleRect.a);

	// Scroller 
	IniWriteInt(file, L"Scroller", L"Red", scroller.r);
	IniWriteInt(file, L"Scroller", L"Green", scroller.g);
	IniWriteInt(file, L"Scroller", L"Blue", scroller.b);
	IniWriteInt(file, L"Scroller", L"Alpha", scroller.a);

	// Options Text
	IniWriteInt(file, L"Options Text", L"Red", options.r);
	IniWriteInt(file, L"Options Text", L"Green", options.g);
	IniWriteInt(file, L"Options Text", L"Blue", options.b);
	IniWriteInt(file, L"Options Text", L"Alpha", options.a);

	// Options Rect
	IniWriteInt(file, L"Options Rect", L"Red", optionsrect.r);
	IniWriteInt(file, L"Options Rect", L"Green", optionsrect.g);
	IniWriteInt(file, L"Options Rect", L"Blue", optionsrect.b);
	IniWriteInt(file, L"Options Rect", L"Alpha", optionsrect.a);
}

void Menu::endMenu() {
	if (menulevel > 0)
	{
		if (optioncount > 16)
		{
			drawText(StringToChar(std::to_string(currentoption) + "/" + std::to_string(optioncount)),
				6, menux - 0.1f, (17 * 0.035f + 0.125f), 0.5f, 0.5f, titleText, false);
			drawRect(menux, (17 * 0.035f + 0.1415f), 0.23f, 0.035f, titleRect);

			if (currentoption == 1) {
				drawSprite("commonmenu", "arrowright", menux, ((16 + 1) * 0.035f + 0.145f), 0.02f, 0.02f, 90, titleText);
			}
			else if (currentoption == optioncount) {
				drawSprite("commonmenu", "arrowright", menux, ((16 + 1) * 0.035f + 0.145f), 0.02f, 0.02f, 270, titleText);
			}
			else {
				drawSprite("commonmenu", "arrowright", menux, ((16 + 1) * 0.035f + 0.14f), 0.02f, 0.02f, 270, titleText);
				drawSprite("commonmenu", "arrowright", menux, ((16 + 1) * 0.035f + 0.15f), 0.02f, 0.02f, 90, titleText);
			}
		}
		else
		{
			drawText(StringToChar(std::to_string(currentoption) + "/" + std::to_string(optioncount)),
				6, menux - 0.1f, ((optioncount + 1) * 0.035f + 0.125f), 0.5f, 0.5f, titleText, false);
			drawRect(menux, ((optioncount + 1) * 0.035f + 0.1415f), 0.23f, 0.035f, titleRect);

			if (currentoption == 1 && optioncount > 1) {
				drawSprite("commonmenu", "arrowright", menux, ((optioncount + 1) * 0.035f + 0.145f), 0.02f, 0.02f, 90, titleText);
			}
			else if (currentoption == optioncount && optioncount > 1) {
				drawSprite("commonmenu", "arrowright", menux, ((optioncount + 1) * 0.035f + 0.145f), 0.02f, 0.02f, 270, titleText);
			}
			else if (optioncount > 1) {
				drawSprite("commonmenu", "arrowright", menux, ((optioncount + 1) * 0.035f + 0.14f), 0.02f, 0.02f, 270, titleText);
				drawSprite("commonmenu", "arrowright", menux, ((optioncount + 1) * 0.035f + 0.15f), 0.02f, 0.02f, 90, titleText);
			}
		}


		UI::HIDE_HELP_TEXT_THIS_FRAME();
		CAM::SET_CINEMATIC_BUTTON_ACTIVE(0);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(10);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(6);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(7);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(9);
		UI::HIDE_HUD_COMPONENT_THIS_FRAME(8);




		if (currentoption > optioncount) currentoption = optioncount;
		if (currentoption < 1) currentoption = 1;
	}
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlNextCamera, true);

	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlPhone, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlVehicleCinCam, true);

	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMichael, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterFranklin, true);

	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterTrevor, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMultiplayer, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlCharacterWheel, true);

	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackLight, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackHeavy, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMeleeAttackAlternate, true);

	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMultiplayerInfo, true);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlMapPointOfInterest, true);
}

void Menu::checkKeys() {
	optionpress = false;
	if (GetTickCount() - Delay > 150) {
		if (KeyDown(VK_INSERT)) {
			opened = !opened;
			Delay = GetTickCount();
			if (opened)
				menu_beep(NAV_OPEN);
			else
				menu_beep(NAV_CLOSED);
		}
		if (!opened)
			return;
		if (getKeyPressed(VK_NUMPAD0) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendCancel)) {
			if (menulevel > 0)
				backMenu();
			else if (menulevel == 0)
				opened = false;
			Delay = GetTickCount();
			menu_beep(NAV_CANCEL);
		}
		if (getKeyPressed(VK_NUMPAD5) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendAccept)) {
			optionpress = true;
			Delay = GetTickCount();
			menu_beep(NAV_SELECT);
		}
		if (getKeyPressed(VK_NUMPAD2) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendDown)) {
			if (currentoption < optioncount)
				currentoption++;
			else
				currentoption = 1;
			Delay = GetTickCount();
			downpress = true;
			menu_beep(NAV_UP_DOWN);
		}
		if (getKeyPressed(VK_NUMPAD8) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlFrontendUp)) {
			if (currentoption > 1)
				currentoption--;
			else
				currentoption = optioncount;
			Delay = GetTickCount();
			uppress = true;
			menu_beep(NAV_UP_DOWN);
		}
		if (getKeyPressed(VK_NUMPAD4) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneLeft)) {
			leftpress = true;
			Delay = GetTickCount();
			menu_beep(NAV_LEFT_RIGHT);
		}
		if (getKeyPressed(VK_NUMPAD6) || CONTROLS::IS_DISABLED_CONTROL_PRESSED(0, ControlPhoneRight)) {
			rightpress = true;
			Delay = GetTickCount();
			menu_beep(NAV_LEFT_RIGHT);
		}
	}
}

