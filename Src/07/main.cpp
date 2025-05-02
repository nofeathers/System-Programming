//#include <map>
//
//int main() {
//	std::map<int, const char*> mapTest;
//	mapTest.insert(std::make_pair(0, "zero"));
//	mapTest.insert(std::make_pair(0, "zero2"));
//	mapTest.insert(std::make_pair(1, "one"));
//	for(auto iter = mapTest.begin(); iter != mapTest.end(); iter++)
//		printf("%d-%s ", iter->first, iter->second);
//
//	mapTest.erase(0);
//	for (auto iter = mapTest.begin(); iter != mapTest.end(); iter++)
//		printf("%d-%s ", iter->first, iter->second);
//	return 0;
//}

//#include <map>
//int main()
//{
//	std::multimap<int, const char*> mapTest;
//	mapTest.insert(std::make_pair(0, "zero"));
//	mapTest.insert(std::make_pair(0, "zero2"));
//	mapTest.insert(std::make_pair(1, "one"));
//	for (auto iter = mapTest.begin(); iter != mapTest.end(); iter++)
//		printf("%d-%s ", iter->first, iter->second);
//
//	mapTest.erase(0);
//	for (auto iter = mapTest.begin(); iter != mapTest.end(); iter++)
//		printf("%d-%s ", iter->first, iter->second);
//	return 0;
//}

//#include <map>
//
//int main() {
//	std::map<int, const char*> mapTest;
//	mapTest.insert(std::make_pair(5, "five"));
//	mapTest.insert(std::make_pair(2, "two"));
//	mapTest.insert(std::make_pair(3, "three"));
//	for (auto iter = mapTest.begin(); iter != mapTest.end(); iter++)
//		printf("%d-%s ", iter->first, iter->second);
//	return 0;
//}

#include <string>

int main() {
	std::string strTest = "Hello World!";
//	printf("%s\n", strTest);
	printf("%s\n", strTest.c_str());
	return 0;
}

