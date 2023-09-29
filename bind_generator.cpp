#include <string>
#include <vector>
#include <format>
using namespace std;
class BindGenerator {
public:
	string generate_bind(string key,vector<string> allWeapons) {
		string bind="bind ";
		string weapons_string="\"";
		for (auto& weapon : allWeapons) {
			weapons_string += "buy ";
			weapons_string += weapon;
			weapons_string += "; ";
		}
		weapons_string += "\"";
		bind += "\"" + key + "\" " + weapons_string;
		return bind;
	}
};