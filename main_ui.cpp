#include <qwidget.h>
#include "keyboard.cpp"
#include <qcombobox.h>
#include <qlabel.h>
#include <QListWidget>
#include <QApplication>
#include <QClipboard>
#include "bind_generator.cpp"
using namespace std;

class UserInterface : public QWidget{
private:
	friend class Keyboard;
	Keyboard* keyboard = new Keyboard;
	QLineEdit* selected_weapon = new QLineEdit;
	QLineEdit* selected_key = new QLineEdit;
	QPushButton* keyboard_button = new QPushButton("Keyboard");
	QPushButton* generate_button = new QPushButton("Generate bind");
	QPushButton* clear_bind = new QPushButton("Clear bind");
	QPushButton* copy_binds = new QPushButton("Copy binds to clipboard");
	QHBoxLayout* layout = new QHBoxLayout;
	QVBoxLayout* items_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_rifle_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_smgs_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_heavy_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_pistol_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_equipement_layout = new QVBoxLayout;
	QVBoxLayout* horizontal_grenades_layout = new QVBoxLayout;
	QComboBox* rifles_box = new QComboBox;
	QComboBox* smgs_box = new QComboBox;
	QComboBox* heavy_box = new QComboBox;
	QComboBox* pistols_box = new QComboBox;
	QComboBox* equipment_box = new QComboBox;
	QComboBox* grenades_box = new QComboBox;
	QStringList rifles_string;
	QStringList smgs_string;
	QStringList heavy_string;
	QStringList pistols_string;
	QStringList equipment_string;
	QStringList grenades_string;
	QLabel* rifles = new QLabel("Rifles");
	QLabel* smgs = new QLabel("SMGs");
	QLabel* heavy = new QLabel("Heavy");
	QLabel* pistols = new QLabel("Pistols");
	QLabel* equipment = new QLabel("Equipemnt");
	QLabel* grenades = new QLabel("Grenades");
	QListWidget* bind_list = new QListWidget;
	QVBoxLayout* bind_list_layout = new QVBoxLayout;
	BindGenerator bind_generator;
	map<string, string> weapons_map;
	map<string, string> bind_map;
	map<string, vector<string>> everyKeyWeapons;
	map<string, string> binds_to_show;
public:
	UserInterface() {
		this->setFixedSize(500, 500);
		this->setWindowTitle("CS:GO Bind Generator");
		this->setWindowIcon(QIcon("main_ico.png"));
		
		init();
		setup();
	}
	void init() {
		QObject::connect(keyboard, &Keyboard::destroyed, [&]() {
			keyboard_button->setEnabled(true);
			keyboard = new Keyboard;
			init();
			});
		QObject::connect(keyboard_button, &QPushButton::clicked, [&]() {
			keyboard->show();
			generate_button->setDisabled(false);
			keyboard_button->setDisabled(true);
			});
		QObject::connect(equipment_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + equipment_box->currentText());
			});
		QObject::connect(grenades_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + grenades_box->currentText());
			});
		QObject::connect(rifles_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + rifles_box->currentText());
			});
		QObject::connect(smgs_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + smgs_box->currentText());
			});
		QObject::connect(pistols_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + pistols_box->currentText());
			});
		QObject::connect(heavy_box, &QComboBox::currentIndexChanged, [&]() {
			selected_weapon->setText("Selected item: " + heavy_box->currentText());
			});
		QObject::connect(copy_binds, &QPushButton::clicked, [&]() {
			string binds_to_copy;
			for (auto bind : binds_to_show) {
				binds_to_copy += bind.second+";";
			}
			binds_to_copy.pop_back();
			QClipboard* clipboard = QGuiApplication::clipboard();
			clipboard->setText(QString::fromStdString(binds_to_copy));
			});
		QObject::connect(clear_bind, &QPushButton::clicked, [&]() {
			binds_to_show.erase(keyboard->lastPressed().toStdString());
			while (!everyKeyWeapons[keyboard->lastPressed().toStdString()].empty())
				everyKeyWeapons[keyboard->lastPressed().toStdString()].pop_back();
			bind_list->clear();
			for (auto& bind : binds_to_show)
			{
				QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bind.second));
				bind_list->addItem(item);
			}
			});
		QObject::connect(generate_button, &QPushButton::clicked, [&]() {
			if(keyboard->lastPressed()!="")
			{
				clear_bind->setDisabled(false);
				selected_key->setText("Last selected key: " + keyboard->lastPressed());
				string string_selected_weapon = selected_weapon->text().toStdString();
				string selected_item;
				for (int i = 15;i < string_selected_weapon.size();i++)
					selected_item += string_selected_weapon[i];
				everyKeyWeapons[keyboard->lastPressed().toStdString()].push_back(weapons_map[selected_item]);
				string bind = bind_generator.generate_bind(keyboard->lastPressed().toStdString(), everyKeyWeapons[keyboard->lastPressed().toStdString()]);
				binds_to_show[keyboard->lastPressed().toStdString()] = bind;
				bind_list->clear();
				for(auto& bind : binds_to_show)
				{
					QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(bind.second));
					bind_list->addItem(item);
				}
			}
			});
		
		
	}
	void setup() {
		weapons_map["Kevlar Vest"] = "vest";
		weapons_map["Kevlar + Helmet"] = "vesthelm";
		weapons_map["Zeus x27"] = "taser 34";
		weapons_map["Defuse Kit"] = "defuser";
		weapons_map["Incendiary"] = "incgrenade";
		weapons_map["Molotov"] = "molotov";
		weapons_map["Decoy"] = "decoy";
		weapons_map["Flashbang"] = "flashbang";
		weapons_map["High Explosive"] = "hegrenade";
		weapons_map["Smoke"] = "smokegrenade";
		weapons_map["FAMAS"] = "famas";
		weapons_map["Galil AR"] = "galilar";
		weapons_map["M4A1-S"] = "m4a1";
		weapons_map["M4A4"] = "m4a1";
		weapons_map["AK-47"] = "ak47";
		weapons_map["SSG 08"] = "ssg08";
		weapons_map["AUG"] = "aug";
		weapons_map["AWP"] = "awp";
		weapons_map["SCAR-20"] = "scar20";
		weapons_map["G3SG1"] = "g3sg1";
		weapons_map["SG 553"] = "sg536";
		weapons_map["MP9"] = "mp9";
		weapons_map["MAC-10"] = "mac10";
		weapons_map["MP7"] = "mp7";
		weapons_map["MP5-SD"] = "mp5";
		weapons_map["UMP-45"] = "ump45";
		weapons_map["P90"] = "p90";
		weapons_map["PP-Bizon"] = "bizon";
		weapons_map["Nova"] = "nova";
		weapons_map["XM1014"] = "xm1014";
		weapons_map["MAG-7"] = "mag7";
		weapons_map["Sawed-Off"] = "sawedoff";
		weapons_map["M249"] = "m249";
		weapons_map["Negev"] = "negev";
		weapons_map["USP-S"] = "hkp2000";
		weapons_map["P2000"] = "hkp2000";
		weapons_map["Glock-18"] = "glock";
		weapons_map["Dual Berettas"] = "elite";
		weapons_map["P250"] = "p250";
		weapons_map["Five-SeveN"] = "fn57";
		weapons_map["Tec-9"] = "tec9";
		weapons_map["CZ75-Auto"] = "fn57";
		weapons_map["Desert Eagle"] = "deagle";
		weapons_map["R8 Revolver"] = "revolver";
		bind_list->setFixedSize(200, 400);
		bind_list_layout->addWidget(bind_list);
		copy_binds->adjustSize();
		bind_list_layout->addWidget(copy_binds);
		generate_button->setDisabled(true);
		clear_bind->setDisabled(true);
		selected_weapon->setStyleSheet("color: blue; background-color: white;");
		selected_weapon->setFixedSize(200, 30);
		selected_weapon->setDisabled(true);
		selected_key->setStyleSheet("color: #FFAA00; background-color: white;");
		selected_key->setFixedSize(200, 30);
		selected_key->setDisabled(true);
		
		rifles_box->setFixedSize(150, 20);
		equipment_box->setFixedSize(150, 20);
		smgs_box->setFixedSize(150, 20);
		heavy_box->setFixedSize(150, 20);
		pistols_box->setFixedSize(150, 20);
		grenades_box->setFixedSize(150, 20);
		keyboard_button->setFixedSize(150, 30);
		generate_button->setFixedSize(150, 30);
		clear_bind->setFixedSize(150, 30);
		rifles_string << "FAMAS" <<"Galil AR" << "M4A4" <<"M4A1-S"<<"AK-47"<<"SSG 08"<<"AUG"<<"SG 553"<<"AWP"<<"SCAR-20"<<"G3SG1";
		smgs_string << "MP9" << "MAC-10" << "MP7" << "MP5-SD" << "UMP-45" << "P90" << "PP-Bizon";
		heavy_string << "Nova" << "XM1014" << "MAG-7" << "Sawed-Off" << "M249" << "Negev";
		pistols_string << "USP-S" << "P2000" << "Glock-18" << "Dual Berettas" << "P250" << "Five-SeveN" << "Tec-9" << "CZ75-Auto" << "Desert Eagle" << "R8 Revolver";
		equipment_string << "Kevlar Vest" << "Kevlar + Helmet" << "Zeus x27" << "Defuse Kit";
		grenades_string << "Incendiary" << "Molotov" << "Decoy" << "Flashbang" << "High Explosive" << "Smoke";
		rifles_box->addItems(rifles_string);
		smgs_box->addItems(smgs_string);
		heavy_box->addItems(heavy_string);
		equipment_box->addItems(equipment_string);
		grenades_box->addItems(grenades_string);
		pistols_box->addItems(pistols_string);
		
		horizontal_equipement_layout->addWidget(equipment);
		horizontal_equipement_layout->addWidget(equipment_box);
		horizontal_grenades_layout->addWidget(grenades);
		horizontal_grenades_layout->addWidget(grenades_box);
		horizontal_rifle_layout->addWidget(rifles);
		horizontal_rifle_layout->addWidget(rifles_box);
		horizontal_smgs_layout->addWidget(smgs);
		horizontal_smgs_layout->addWidget(smgs_box);	
		horizontal_heavy_layout->addWidget(heavy);
		horizontal_heavy_layout->addWidget(heavy_box);
		horizontal_pistol_layout->addWidget(pistols);
		horizontal_pistol_layout->addWidget(pistols_box);
		items_layout->addLayout(horizontal_equipement_layout);
		items_layout->addLayout(horizontal_grenades_layout);
		items_layout->addLayout(horizontal_rifle_layout);
		items_layout->addLayout(horizontal_smgs_layout);
		items_layout->addLayout(horizontal_heavy_layout);
		items_layout->addLayout(horizontal_pistol_layout);
		items_layout->addWidget(selected_weapon);
		items_layout->addWidget(selected_key);
		items_layout->addWidget(keyboard_button);
		items_layout->addWidget(generate_button);
		items_layout->addWidget(clear_bind);
		layout->addLayout(items_layout);
		layout->addLayout(bind_list_layout);
		this->setLayout(layout);
		
	}
	
};