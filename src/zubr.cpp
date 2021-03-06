// zubr.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include "zbrstr.h"
#include "zbrmap.h"
#include "zbrtree.h"
#include "zbrdic.h"
#include "iup.h"

Map dic = NULL;

int item_open_eng_dic(Ihandle* item_eng_dic) {
	Ihandle *dlg, *text, *item_tolk_dic, *item_rus_dic;
	
	text = IupLabel(NULL);
	dlg = IupDialog(text);
	item_tolk_dic = IupGetDialogChild(item_eng_dic, "TOLK");
	item_rus_dic = IupGetDialogChild(item_eng_dic, "RUS");

	IupSetAttribute(text, "TITLE", "Зубр пасется на лугу,\nподождите немножко...");
	IupSetAttribute(text, "FONT", "Comic Sans MS, 12");
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "TITLE", "Ждёмс...");
	IupSetAttribute(item_eng_dic, "VALUE", "YES");
	IupSetAttribute(item_tolk_dic, "VALUE", "NO");
	IupSetAttribute(item_rus_dic, "VALUE", "NO");

	IupShowXY(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);

	close_dic(dic);
	dic = create_map();
	if (!open_dic("eng_rus.zbr", dic)) {
		IupMessage("Ошибка", "Зубр не нашёл словарь :(");
	}		
	IupDestroy(dlg);
	return IUP_DEFAULT;
}

int item_open_rus_dic(Ihandle* item_rus_dic) {
	Ihandle *dlg, *text, *item_tolk_dic, *item_eng_dic;

	text = IupLabel(NULL);
	dlg = IupDialog(text);
	item_tolk_dic = IupGetDialogChild(item_rus_dic, "TOLK");
	item_eng_dic = IupGetDialogChild(item_rus_dic, "ENG");

	IupSetAttribute(text, "TITLE", "Будем зубра, подождите немножко...");
	IupSetAttribute(text, "FONT", "Comic Sans MS, 12");
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "TITLE", "Ждёмс...");
	IupSetAttribute(item_rus_dic, "VALUE", "YES");
	IupSetAttribute(item_tolk_dic, "VALUE", "NO");
	IupSetAttribute(item_eng_dic, "VALUE", "NO");

	IupShowXY(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);

	close_dic(dic);
	dic = create_map();
	if (!open_dic("rus_eng.zbr", dic)) {
		IupMessage("Ошибка", "Зубр не нашёл словарь :(");
	}		
	IupDestroy(dlg);
	return IUP_DEFAULT;
}

int item_open_tolk_dic(Ihandle* item_tolk_dic) {
	Ihandle *dlg, *text, *item_eng_dic, *item_rus_dic;

	text = IupLabel(NULL);
	dlg = IupDialog(text);
	item_eng_dic = IupGetDialogChild(item_tolk_dic, "ENG");
	item_rus_dic = IupGetDialogChild(item_tolk_dic, "RUS");

	IupSetAttribute(text, "TITLE", "Зубр пасется на лугу,\nподождите немножко...");
	IupSetAttribute(text, "FONT", "Comic Sans MS, 12");
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "TITLE", "Ждёмс...");
	IupSetAttribute(item_tolk_dic, "VALUE", "YES");
	IupSetAttribute(item_eng_dic, "VALUE", "NO");
	IupSetAttribute(item_rus_dic, "VALUE", "NO");

	IupShowXY(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);

	close_dic(dic);
	dic = create_map();
	if (!open_dic("tolk.zbr", dic)) {
		IupMessage("Ошибка", "Зубр не нашёл словарь :(");
	}
	IupDestroy(dlg);
	return IUP_DEFAULT;
}

int item_exit_action_cb(Ihandle* item_exit) {
	Ihandle* dlg = IupMessageDlg();

	IupSetAttribute(dlg, "DIALOGTYPE", "WARNING");
	IupSetAttribute(dlg, "TITLE", "ZUBR словарь");
	IupSetAttribute(dlg, "BUTTONS", "OKCANCEL");
	IupSetAttribute(dlg, "VALUE", "Как, вы уже уходите? :(");
	IupSetAttribute(dlg, "FONT", "Comic Sans MS, 9");

	IupPopup(dlg, IUP_CURRENT, IUP_CURRENT);

	if (IupGetAttribute(dlg, "BUTTONRESPONSE")[0] == '1') {
		IupDestroy(dlg);
		return IUP_CLOSE;
	}

	IupDestroy(dlg);
	return IUP_DEFAULT;
}

int button_search(Ihandle* button) {
	Ihandle *multitext, *text;
	char *word, *translate;
	
	if (!dic) {
		IupMessage("Ой", "Выберите словарь");
		return IUP_DEFAULT;
	}

	multitext = IupGetDialogChild(button, "MULTITEXT");
	text = IupGetDialogChild(button, "TEXT");
	word = IupGetAttribute(text, "VALUE");
	translate = search_in_dic(word, dic);
	
	if (!translate) {
		IupSetAttribute(multitext, "VALUE", "Слово не найдено :(");
		return IUP_DEFAULT;
	}

	IupSetAttribute(multitext, "VALUE", translate);
	IupSetAttribute(text, "VALUE", word);
	return IUP_DEFAULT;
}

int item_font_action_cb(Ihandle* item_font) {
	Ihandle *multitext, *fontdlg;
	char* font;
	
	multitext = IupGetDialogChild(item_font, "MULTITEXT");
	fontdlg = IupFontDlg();
	font = IupGetAttribute(multitext, "FONT");

	IupSetStrAttribute(fontdlg, "VALUE", font);
	IupSetAttributeHandle(fontdlg, "PARENTDIALOG", IupGetDialog(item_font));

	IupPopup(fontdlg, IUP_CENTERPARENT, IUP_CENTERPARENT);

	if (IupGetInt(fontdlg, "STATUS") == 1) {
		font = IupGetAttribute(fontdlg, "VALUE");
		IupSetStrAttribute(multitext, "FONT", font);
	};

	IupDestroy(fontdlg);
	return IUP_DEFAULT;
}

int item_about_action(void) {
	IupMessage("О программе", 
		"   ZUBR словарь\n\nАвторы:\n\n"
		"    Зубарев Алексей		  _     _\n"
		"    Луцкий Степан		((____))\n"
		"    Луцкий Фёдор		 [ о ~ ]\n"
		"    Луцкий Никита		 '\\     /' \n"
		"    Лебедев Фёдор		  ('__')\n"
		"    Косых Андрей\n"
		"    Калтыгин Глеб		 ZUBR\n\n"
		" Все права защищены!");
	return IUP_DEFAULT;
}

int item_cool_action(void) {
	IupMessage("Справка", "Зубры - хорошие ребята!!!");
	return IUP_DEFAULT;
}

int item_turbo_action(void) {
	Ihandle *dlg, *text;
	
	if (!dic) {
		IupMessage("Ой", "Выберите словарь");
		return IUP_DEFAULT;
	}

	text = IupLabel(NULL);
	dlg = IupDialog(text);
	IupSetAttribute(text, "TITLE", "Зубр ускоряется...");
	IupSetAttribute(text, "FONT", "Comic Sans MS, 12");
	IupSetAttribute(dlg, "MENUBOX", "NO");
	IupSetAttribute(dlg, "TITLE", "Ждёмс...");
	IupShowXY(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);
	
	optimization(dic);
	
	IupDestroy(dlg);
	return IUP_DEFAULT;
}

int main() {
	Ihandle *dlg, *vbox, *hbox, *multitext, *menu, *text, *button;
	Ihandle *format_menu, *dic_menu, *help_menu;
	Ihandle *sub_menu_format, *sub_menu_dic, *sub_menu_help;
	Ihandle *sub_menu_exit, *exit_menu;
	Ihandle	*item_font, *item_open_tolk, *item_open_eng, *item_turbo;
	Ihandle *item_open_rus, *item_about, *item_cool, *item_exit;

	IupOpen(NULL, NULL);

	text = IupText(NULL);
	IupSetAttribute(text, "EXPAND", "HORIZONTAL");
	IupSetAttribute(text, "NAME", "TEXT");
	IupSetAttribute(text, "FONT", "Comic Sans MS, 12");
	IupSetCallback(text, "K_CR", (Icallback)button_search);

	button = IupButton("ZаZUBRить!", NULL);
	IupSetAttribute(button, "FONT", "Comic Sans MS, 12");
	IupSetCallback(button, "ACTION", (Icallback)button_search);

	multitext = IupText(NULL);
	IupSetAttribute(multitext, "MULTILINE", "YES");
	IupSetAttribute(multitext, "EXPAND", "YES");
	IupSetAttribute(multitext, "FONT", "Comic Sans MS, 12");
	IupSetAttribute(multitext, "NAME", "MULTITEXT");
	IupSetAttribute(multitext, "WORDWRAP", "YES");

	item_font = IupItem("Текст...", NULL);
	item_about = IupItem("О программе...", NULL);
	item_cool = IupItem("Справка", NULL);
	item_open_tolk = IupItem("Толковый", NULL);
	item_open_eng = IupItem("Англо-Русский", NULL);
	item_open_rus = IupItem("Русско-Английский", NULL);
	item_turbo = IupItem("Turbo режим", NULL);
	item_exit = IupItem("Выйти", NULL);

	IupSetAttribute(item_open_tolk, "NAME", "TOLK");
	IupSetAttribute(item_open_eng, "NAME", "ENG");
	IupSetAttribute(item_open_rus, "NAME", "RUS");

	IupSetCallback(item_open_eng, "ACTION", (Icallback)item_open_eng_dic);
	IupSetCallback(item_open_tolk, "ACTION", (Icallback)item_open_tolk_dic);
	IupSetCallback(item_open_rus, "ACTION", (Icallback)item_open_rus_dic);
	IupSetCallback(item_turbo, "ACTION", (Icallback)item_turbo_action);
	IupSetCallback(item_font, "ACTION", (Icallback)item_font_action_cb);
	IupSetCallback(item_about, "ACTION", (Icallback)item_about_action);
	IupSetCallback(item_cool, "ACTION", (Icallback)item_cool_action);
	IupSetCallback(item_exit, "ACTION", (Icallback)item_exit_action_cb);

	format_menu = IupMenu(
		item_font,
		NULL);
	help_menu = IupMenu(
		item_cool,
		item_about,
		NULL);
	dic_menu = IupMenu(
		item_open_tolk,
		item_open_eng,
		item_open_rus,
		item_turbo,
		NULL);
	exit_menu = IupMenu(
		item_exit,
		NULL);

	sub_menu_format = IupSubmenu("Формат", format_menu);
	sub_menu_help = IupSubmenu("Помощь", help_menu);
	sub_menu_dic = IupSubmenu("Словари", dic_menu);
	sub_menu_exit = IupSubmenu("Выход", exit_menu);

	menu = IupMenu(
		sub_menu_format,
		sub_menu_dic,
		sub_menu_help,
		sub_menu_exit,
		NULL);
	IupSetAttribute(item_exit, "FONT", "Comic Sans MS, 9");

	hbox = IupHbox(text, button, NULL);
	IupSetAttribute(hbox, "MARGIN", "10x10");
	IupSetAttribute(hbox, "GAP", "10");
	IupSetAttribute(hbox, "ALIGNMENT", "ACENTER");
	
	vbox = IupVbox(hbox, multitext, NULL);

	dlg = IupDialog(vbox);
	IupSetAttributeHandle(dlg, "MENU", menu);
	IupSetAttribute(dlg, "TITLE", "ZUBR словарь");
	IupSetAttribute(dlg, "SIZE", "HALFxHALF");

	IupSetAttributeHandle(NULL, "PARENTDIALOG", dlg);

	IupShowXY(dlg, IUP_CENTERPARENT, IUP_CENTERPARENT);
	IupSetAttribute(dlg, "USERSIZE", NULL);

	IupMainLoop();

	IupClose();
	return 0;
}
