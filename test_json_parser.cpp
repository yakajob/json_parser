
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/nvp.hpp>

#include <synoabk/json_parser.hpp>

struct Cat {
	std::string color;
	int weight = 0;

	Cat(){}
	Cat(const std::string &colorIn, const int weightIn): color(colorIn), weight(weightIn){}

    template <typename Archive> void serialize(Archive &ar, unsigned) 
    {
        ar & BOOST_SERIALIZATION_NVP(color)
           & BOOST_SERIALIZATION_NVP(weight);
    }
};

struct Dog {
	std::string barkType;
	std::string color;
	int weight = 0;
	std::list<int> numbers;
	std::list<Cat> cats;
	Cat cat;
	std::vector<int> birds;

    template <typename Archive> void serialize(Archive &ar, unsigned) 
    {
        ar & BOOST_SERIALIZATION_NVP(barkType)
           & BOOST_SERIALIZATION_NVP(color)
           & BOOST_SERIALIZATION_NVP(weight)
		   & BOOST_SERIALIZATION_NVP(numbers)
		   & BOOST_SERIALIZATION_NVP(birds)
		   & BOOST_SERIALIZATION_NVP(cats)
		   & BOOST_SERIALIZATION_NVP(cat);
    }
};

static void json_test()
{
	Dog dog;
	dog.color = "green";
	dog.barkType = "whaf";
	dog.weight = 30;
	dog.numbers = {123, 456};
	dog.cat = Cat("red", 11);
	dog.cats.emplace_back("black", 12);
	dog.cats.emplace_back("white", 13);
	dog.birds = {789, 654};

	Json::Value jsonDog = objToJson(dog); // produces {"color":"green", "barkType":"whaf", "weight": 30}
	ERR_MSG("JIM: jsonDog[%s]", synoabk::fmt::to_string(jsonDog).c_str());

	Dog dog2;
	jsonToObj(jsonDog, dog2);
	ERR_MSG("JIM: jsonDog[%s][%s][%d], numbers[%s], cat[%s][%d], birds[%s]", 
					dog2.color.c_str(), dog2.barkType.c_str(), dog2.weight,
					fmt::join(dog2.numbers, ",").c_str(),
					dog2.cat.color.c_str(), dog2.cat.weight,
					fmt::join(dog2.birds, ",").c_str());
}
