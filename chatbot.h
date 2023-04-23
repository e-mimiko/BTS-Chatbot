// chatbot.h
//This program creates a chatbot. The chatbot follows
//the eliza style chatbot and goes beyond the eliza style bot
//by answering question and saving user input to be used later on
//
//
//CMPT 125
//Created by Emi Mimiko
//
//July 21, 2020.


#include <string>
#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <regex>
using namespace std;
//
// Your chatbot class goes here. Make sure it works with chatbot_driver.cpp.

int MAX_RESP = 3;
int counter = 0;
int ask_return;


struct directory
{
	string keyword_;
	vector<string>database_;
};

struct transpose
{
	string first_;
	string second_;
};

struct misc_input
{
	string unsure_resp;
	string repeat_resp;
};

struct grammar
{
	string adjective_;
	string noun_;
};

struct match_template
{
	string templates;
};

class Chatbot
{
	string name_;
	string input_;
	string output_;
	string prev_input_;
	string old_input_;
	string first_match_;
	string second_match_;

public:
	
//constructor:
	Chatbot(string name)
	: name_(name), prev_input_(""), input_(""), output_(""), old_input_(""), first_match_(""), second_match_("")
	{}

//--	
		
	string get_name()
	{
		return name_;
	}

	void tell(string& input)
	{
		input_ = input;
		
	}

//
//Function declarations:
//
	string match();
	string strip(string& input_s);
	int isPrev_input();
	string get_exact_match(string& input);
	string construct_reply(string& input);
	string keyword_match(string& input);
	void make_transposition(string& str, string& temp);
	int ask();
	void clear(string& input);

//--

	string get_reply()
	{
		counter++;
		output_ = match();
		prev_input_ = input_;
		return output_;
	}

//----

};

//===============
//	STRUCTS
//===============


//This is the main directory for the keywords and their reponses
//Each keyword has 3 possible responses
//Words with %1% are to be replaced later
struct directory dir[] = 
{
	{"how are you", {"I'm good. You?", "I'm doing great", "Why"}},
	{"are you having a good day", {"Yes. You?", "I'm always having a good day", "Why"}},
	{"learn something", {"I can teach you about KPOP. Ask me", "Ask me about KPOP!", 
	"You can ask me anything about KPOP!"}},
	{"teach", {"I can teach you about KPOP. Ask me", "Ask me anything about kpop!", "Ask me about kpop"}},
	{"what is kpop", {"It is short for Korean Pop. Most consists of boy bands and girl groups", 
	"It means Korean POP. There are an ernomous amount of boybands and girl groups", 
	"Its a niche of music originally from South Korea.\nMade up of boy bands and girl groups.\nThere can be over 13 members in a group/band" }},
	{"biggest band", {"BTS! They are the biggest", "BTS maybe", 
	"I believe BTS. They are the first group to perform on the Billboards Awards" }},
	{"favourite band", {"BTS! They are the biggest.", "BTS hands down.", 
	"No one beats BTS!" }},
	{"why do you like bts", {"Watching BTS is like watching friends play around. No malice amongst them", "TTheir songs speaks to me", 
	"They are hilarious to watch" }},
	{"favourite song", {"I like SEA a lit", "SEA is their best song to me", 
	"I like lots of them but SEA takes the cake for me" }},
	{"sea", {"No reason", "Just because", 
	"Its a great song. Very emotional." }},
	{"members", {"Jimin, Tae, Jhope, RM, Suga, Jungkook & Jin are the 7 members members", 
	"There are 4 vocalists and 3 rapper members", "There are 7 members in total" }},
	{"favourite member", {"Jimin is the best!", "I really like Jhope", "Jimin & Jhope. I cant choose."}},
	{"like jimin", {"He has a sweet voice !", "He seems like genuinely good person", 
	"He has a friendly personality and is super sweet"}},
	{"like jhope", {"He's super talented.", 
	"He dances, sings, rap and has no idea who naruto is. What's there not to love lol", 
	"He is very accomodating. Seems like a nice guy to hang with"}},
	{"hello", {"Hi there", "What's up", "Hey"}},
	{"whats up", {"Nothing much", "What's up", "Hey"}},
	{"thanks", {"You are quite welcome", "No problem","Happy to help as always" }},
	{"i saw", {"How does%1% make you feel", "And?", "Interesting that you saw%1%"}},
	{"can you", {"Don't you believe I can%1%", "You want me to be able to%1%?", "I wish :("}},
	{"will you", {"Do you believe I will%1%", "You want me to be able to%1%?", "I wish :("}},
	{"will i", {"How would I know if you will%1%", "You again huh?", "I dont know really :("}},
	{"can i", {"Why do you want to %1%", "You want to%1%?", "You can do whatever, within reason though"}},
	{"i am", {"Why are you%1%?", "How does being%1% make you feel?", "Why do you think you are%1%"}},
	{"do you", {"I'm not too certain?", "Possibly", "What do you think?"}},
	{"you are", {"What makes you think I am%1%?", "Why do you think I am%1%?", "That's an opinion %1%" }},
	{"i can", {"What makes you think you can %1%?", "Why do you think you can%1%?","Its Interesting you think you can%1%"}},
	{"i like", {"Why do you like%1%?", "What makes you like%1%?","Its interesting you like%1%" }},
	{"i love", {"Why do you love%1%?", "What makes you love%1%?","Why do you think you love%1%?"}},
	{"i hate", {"Why do you hate%1%?", "What makes you hate%1%?","It is always good to use softer words, dont you think?"}},
	{"what", {"Why do you ask?", "Does that question interest you", "What do you think?" }},
	{"because", {"Is that the real reason?", "What other reason might there be","Does that reason tell you something?" }},
	{"i dont know", {"Why do you think that is", "That's perfectly okay","I have no clue either" }},
	{"i want", {"Why do you want%1%?", "is there a reason why you want%1%","It is quite understandable to want%1% I think" }},
	{"i feel", {"Why do you feel%1%?", "is there a reason why you feel%1%","It is quite understandable to feel%1% I think" }},
	{"bye", {"See ya!", "Nice speaking to you","Bye Bye!" }},
	{"sorry", {"That's okay", "Why do you apologize","Bye Bye!" }},
	{"yes", {"Quite a perspective", "Are you really saying yes?","Do you think yes is the correct thing to say" }},
	{"yeah", {"Quite a perspective", "Are you really saying yes?","Do you think yes is the correct thing to say" }},
	{"no", {"That's okay", "Quite a perspective","Why no though" }},
	{"he is", {"Right?", "I agree", "I'd have to agree"}},
	{"she is", {"Right?", "I agree", "I'd have to agree"}},
	{"lol", {"I can be quite funny", "That wasnt a joke","Hehe" }},
	{"why", {"Good question. Who knows", "Must there be a reason", "What's your guess"}},
	{"that", {"Why do you think so", "You think so?", "I guess"}},
	{"you think", {"We aren't talking about me now, are we?", "Does it matter what I think?", "Possibly"}},
	{"hi", {"Hi there", "What's up", "Hey"}},
	{"i", {"Why is that?", "Oh really?","Do you enjoy talking about yourself?" }},
	{"you", {"Why do you want to talk about me?", "Lets talk you for now, okay?","Do you enjoy talking about others?" }},
	{"not", {"Thats too bad", "That's your opinion","Why not?" }}


};


//These are the words to be transposed 
struct transpose transpose_dir[] = 
{
	{"am", "are"}, {"are", "am"}, {"was", "were"}, {"were", "was"}, {"you", "me"}, {"me", "you"},
	{"id", "you would"}, {"you would", "id"}, {"youd", "i would"}, {"i would", "youd"}, 
	{"you are", "I am"}, {"i am", "you are"},{"ive", "are"}, {"are", "ive"},
	 {"my", "your"}, {"your", "my"}, 
	
};

//These are the responses, 
//	1. If there is no match for the user input 
//	2. If the user is repeating themselves
struct misc_input misc_dir[] = 
{
	{"I'm listening", "You're repeating yourself"}, {"Go on", "You just said that"}, 
	{"Tell me more", "Why are you repeating yourself"}, {"Hmmm...", "Heard you the first time"}
};

//These are the feeling words that trigger the chatbot to form a response based on previous inputs 
//Consists of the adjective and noun version of the word
struct grammar feelings_dir[] = 
{
	{"worried", "worry"}, {"sad", "sadness"}, 
	{"anxious", "anxiety"}, {"angry", "anger"},
	{"guilty", "guilt"}
};

//These are the responses for the chatbot to use to create a response to the feeling words
struct match_template feel_resp[] = 
{
	{"Do you think your %1% is because of your%2%?"},
	{"Do you think you are %1% because of your%2%?"},
	{"Is it possible that your %1% is because of your%2%?"},
	{"Do you think you are %1% because of%2%?"}
};


// Size of each directory
size_t feelings_dir_sz = sizeof(feelings_dir)/sizeof(feelings_dir[0]);

size_t misc_dir_sz = sizeof(misc_dir)/sizeof(misc_dir[0]);

size_t transp_size = sizeof(transpose_dir)/sizeof(transpose_dir[0]);

size_t dir_size = sizeof(dir)/sizeof(dir[0]);

size_t feel_resp_dir = sizeof(feel_resp)/sizeof(feel_resp[0]);


//===============
// FUNCTIONS
//===============



//This function strips the input of any punctuation
//and changes the words to be all lower case
string Chatbot::strip(string& input_s) 
{
	//Sources:
	//for removing punctuation: geekforgeeks/removinggivenstring...
	//for removing uppercase: stackoverflow/questions/26316517
	
	string input = input_s;
	transform(input.begin(), input.end(), input.begin(), ::tolower); 
	int len = input.size();
	for (int i = 0; i < len; i++)
	{
		if ( ispunct(input[i]))
		{
			input.erase(i--, 1);
			len = input.size();
		}
	}
	return input;
}

//This is the fucntion that encompasses all the other functions
//This the the function called in get_reply function
string Chatbot::match()
{

	string input = strip(input_);

	if (isPrev_input() == 1)
	{
		int random = rand()%misc_dir_sz;
		return misc_dir[random].repeat_resp;
	}

	string exact_match_return = get_exact_match(input);
	if (!exact_match_return.empty())
	{
		return exact_match_return;
	}

	string feel_func_return = construct_reply(input);
	if (!feel_func_return.empty())
	{
		return feel_func_return;
	}
	
	return keyword_match(input);

}

//This function returns 1 if user repeats a sentence, 0 otherwise.
int Chatbot::isPrev_input()
{
	if (prev_input_ == input_)
	{
		return 1;
	}
	return 0;
}


//This function allows the chatbot to ask the user a question
// Returns 1 once there is a valid question that can be asked
int Chatbot::ask()
{
	
	old_input_ = input_;
	return 1;
	
}


//This functions sets the given string to the empty string
void Chatbot::clear(string& input)
{
	input = "";
}


//This function looks for an exact, word for word totalmatch between the input and the keyword.
//Returns only if the sentence and keyword is the same without any modification
string Chatbot::get_exact_match(string& input)
{
	string match = "";
	for (int i = 0; i < dir_size; i++)
	{
		int keyword_size = (dir[i].keyword_).size();
		if (input == dir[i].keyword_)
		{
			int random = rand()%MAX_RESP;
			match = dir[i].database_[random];
		}
	}
	return match;
}

//This function creates a new responses based on previous inputs
//It will use words from the feelings_dir to formulaye a response
string Chatbot::construct_reply(string& input)
{
	string match_pair = "";
	string temp = "";
	int marker;
	for (int i = 0; i < feelings_dir_sz; i++)
	{
		int adj_sz = (feelings_dir[i].adjective_).size();

		//searching for a keyword.
		if ( ( (input.find(feelings_dir[i].adjective_)) != string::npos) &&  first_match_.empty() )
		{
			size_t space_pos;
			if ((space_pos = input.find_last_of(" ")) != string::npos)
			{
				//stores the last part of the string in a variable
				first_match_ = input.substr(space_pos);

				//makes sure the word found and  is not a keyword itself
				if ( (first_match_.find(feelings_dir[i].adjective_) != string::npos) || 
					(first_match_.find(feelings_dir[i].noun_) != string::npos) )
				{
					clear(first_match_);
				}
			}
		}
		else //if the first word is not stored, then loop exits here. 
		{

			if ( ((input.find(feelings_dir[i].adjective_)) != string::npos) && 
				(!first_match_.empty()) && second_match_.empty() )
			{
				second_match_ = feelings_dir[i].adjective_;
				match_pair = feelings_dir[i].noun_;
				marker = 0;
			}
			else if ( ((input.find(feelings_dir[i].noun_)) != string::npos) &&
				 (!first_match_.empty()) && second_match_.empty())
			{
				second_match_ = feelings_dir[i].noun_;
				match_pair = feelings_dir[i].adjective_;
				marker = 1;
			}
		}
		//if both first and second word has been gotten, this loop is executed
		if ( (!first_match_.empty()) && (!second_match_.empty()) )
		{
			int random = rand()%(feel_resp_dir-1);
			temp = feel_resp[random].templates;
			//if the string with the word does not have my i.e ... my studies
			//use the 4th response in the feel_resp struct
			if ( (prev_input_.find(" my ") == string::npos) ) 
				{
					random = 3;
					temp = feel_resp[random].templates;
				}
			//Depending on the words gotten, the word is swapped with its pair
			//i.e if anxious is gotten, anxiety is used instead to make it a 
			//correct english sentence.
			if (random == 0)
			{
				if (marker == 0)
				{
					temp = regex_replace(temp, regex("%1%"), match_pair);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
				else
				{
					temp = regex_replace(temp, regex("%1%"), second_match_);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
			}
			if (random == 1)
			{
				if (marker == 0)
				{
					temp = regex_replace(temp, regex("%1%"), second_match_);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
				else
				{
					temp = regex_replace(temp, regex("%1%"), match_pair);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
			}
			if (random == 2)
			{
				if (marker == 0)
				{
					temp = regex_replace(temp, regex("%1%"), match_pair);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
				else
				{
					temp = regex_replace(temp, regex("%1%"), second_match_);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
			}
			if (random == 3)
			{
				if (marker == 0) 
				{
					temp = regex_replace(temp, regex("%1%"), second_match_);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
				else
				{
					temp = regex_replace(temp, regex("%1%"), match_pair);
					temp = regex_replace(temp, regex("%2%"), first_match_);
				}
			}
			clear(first_match_);
			clear(second_match_);			
		}	
	}
	return temp;
}

//This function mactches the keywords to a possible response. 
//Will do a tansposition if necessary
string Chatbot::keyword_match(string& input)
{
	
	int pos;
	int three = 3;
	for (int i = 0; i < dir_size; i++)
	{	
		
		int keyword_size = (dir[i].keyword_).size();
		if ((pos = input.find(dir[i].keyword_)) != string::npos)
		{
			if (( (pos+keyword_size) <= input.size()) && !(isalpha(input[pos+keyword_size])))
			{
				//Sources:
				//stackoverflow/questions/4643512/replace-
				//cplusplus/references/string/string/string/substr

				if ( (old_input_.empty()) && (i >= 0 && i <= three) )
				{
					ask_return = ask();
				}
				string str = input.substr(pos+keyword_size);
				int random = rand()%MAX_RESP;
				string temp = dir[i].database_[random];

				//checks if there is transposition to be done
				make_transposition(str, temp);			
				return temp;
			}
			
		}
	}

	//if no match, will check if there is a question to be asked
	if ((ask_return == 1) && (counter > 5))
	{
		counter = 0;
		ask_return = 0;
		string temp_old_input = old_input_;
		clear(old_input_);
		return temp_old_input;
	}

	//If no other option, one misc_directory's ususre defauly response is used.
	int random = rand()%misc_dir_sz;
	return (misc_dir[random].unsure_resp);
}

//This function will make the necessary transposition
//It will locate the %1% sign and replace that
void  Chatbot::make_transposition(string& str, string& temp)
{
	for (int j = 0; j < transp_size; j++)
	{
		string place_hold;
		int pos_t = str.find(transpose_dir[j].first_);
		int word_size = (transpose_dir[j].first_).size();
		if (( pos_t != string::npos )) 
		{
			if (!(isalpha(str[pos_t+word_size])))
			{
				string str2 = transpose_dir[j].second_;
				place_hold = regex_replace(str, regex(transpose_dir[j].first_), str2);

				if (temp.find("%1%") != string::npos)
				{
					temp = regex_replace(temp, regex("%1%"), place_hold);
				}
			}
		}
		else if (j == transp_size - 1)
		{
			if (temp.find("%1%") != string::npos)
			{
				temp = regex_replace(temp, regex("%1%"), str);
			}
		}

	}
}