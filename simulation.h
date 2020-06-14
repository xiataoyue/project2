/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "server.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>



// TODO: Declare your functions in this header file.
// Hint: You may need these request handling functions.
void init_user(string& filename, Server_t& server);
void init_post(Server_t& server, User_t *users, Tag_t *tags, int& tag_num, int& count, string& filename);

User_t *get_user(Server_t& server, const string& name);
void find_user(ifstream& file, Server_t& server, User_t *user[], unsigned int number);
int catch_user(User_t *users, unsigned int num, const string& name);
int catch_tag(Tag_t tags[], unsigned int num, string& name);
int add_tag(Tag_t tags[], int& num, string& content, int score);
void remove_user(User_t *users[], int num, User_t *target);

void like(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int num);
void unlike(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int num);
void comment(Server_t& server, User_t *users, Tag_t *tags, string& username1, string &username2, int num, string& text);
void uncomment(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int postnum, int commentnum);
void post(Server_t& server, User_t *users, Tag_t *tags, string& username, string title, string *tagname, string text, int tagnum);
void delete_post(Server_t& server, User_t *users, Tag_t *tags, int num, string& username);
void refresh(Server_t& server, User_t *users, string& username);
bool compare(Tag_t& tag1, Tag_t& tag2);
void trending(Server_t& server, Tag_t *tags, int num);
void logfile_process(Server_t& server, User_t *users, Tag_t *tags, string path);

string rela_judge(User_t *visitor, User_t *target);
/*
void visit(...);
void trending(...);
void refresh(...);
void follow(...);
void unfollow(...);
void like(...);
void unlike(...);
void comment(...);
void uncomment(...);
void post(...);
void unpost(...);
*/

/* Helper Functions */

// Printing
void printUser(User_t& user, const string& relationship);
void printPost(Post_t& post);
void printTag(const Tag_t& tag, unsigned int rank);

