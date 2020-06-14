/*
 * This is VE280 Project 2, SU2020.
 * Written by Ziqiao Ma and Zhuoer Zhu.
 * Latest Update: 5/29/2020.
 * All rights reserved.
 */

#include "simulation.h"

// TODO: Define your functions in this header file.

/* Helper Functions */
void init_user(string& filename, Server_t& server){
    ifstream usernamefile(filename);
    if(!usernamefile.is_open()) {
        ostringstream Ostream;
        Ostream << "Error: Cannot open file " << filename << "!" << endl;
        throw Exception_t(FILE_MISSING, Ostream.str());
    }
    string name; string user_directory;
    getline(usernamefile, user_directory);
    while(getline(usernamefile, name))
    {
        if(server.user_num >= MAX_USERS){
            ostringstream Ostream;
            Ostream << "Error: Too many users!" << endl;
            Ostream << "Maximal number of users is " << MAX_USERS << "." << endl;
            throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
        }
        server.user[server.user_num].username = name;
        server.user_num ++;
    }
    usernamefile.close();
}

void init_post(Server_t& server, User_t *users, Tag_t *tags, int& tag_num, int& count, string& filename){
    int i, j, k;
    int postsnum, likenum, commentnum;
    int followingnum, followernum;
    string str, temp;
    char ch;
    for(i = 0; i < server.user_num; i++) {
        str = filename + server.user[i].username + "/user_info";
        ifstream file(str);

        if (!file.is_open()) {
            ostringstream Ostream;
            Ostream << "Error: Cannot open file " << str << "!" << endl;
            throw Exception_t(FILE_MISSING, Ostream.str());
        } else {
            file >> postsnum;
            if (postsnum > MAX_POSTS) {
                ostringstream Ostream;
                Ostream << "Error: Too many posts for user " << server.user[i].username << "!" << endl;
                Ostream << "Maximal number of posts is " << MAX_POSTS << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
            }
            server.user[i].num_posts = postsnum;
            file.get(ch);

            file >> followingnum;
            if (followingnum > MAX_FOLLOWING) {
                ostringstream Ostream;
                Ostream << "Error: Too many followings for user " << server.user[i].username << "!" << endl;
                Ostream << "Maximal number of following is " << MAX_FOLLOWING << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
            }
            server.user[i].num_following = followingnum;
            file.get(ch);
            find_user(file, server, server.user[i].following, server.user[i].num_following);

            file >> followernum;
            if (followernum > MAX_FOLLOWERS) {
                ostringstream Ostream;
                Ostream << "Error: Too many followers for user " << server.user[i].username << "!" << endl;
                Ostream << "Maximal number of followers is " << MAX_FOLLOWERS << "." << endl;
                throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
            }
            server.user[i].num_followers = followernum;
            file.get(ch);
            if (followernum == 0) file.close();
            find_user(file, server, server.user[i].follower, server.user[i].num_followers);
            file.close();
        }
    }

    for(i = 0; i < server.user_num; i++){
        for(j = 1; j <= server.user[i].num_posts; j++){
            server.user[i].posts[j].owner = &server.user[i];

            temp = filename + server.user[i].username + "/posts/" + to_string(j);
            ifstream post(temp);
            if(!post.is_open()){
                ostringstream Ostream;
                Ostream << "Error: Cannot open file " << temp << "!" << endl;
                throw Exception_t(FILE_MISSING, Ostream.str());
            }
            else {
                getline(post, server.user[i].posts[j].title);

                while (getline(post, temp) && temp[0] == '#') {
                    if(tag_num >=MAX_TAGS){
                        ostringstream Ostream;
                        Ostream << "Error: Too many tags for post " << server.user[i].posts[j].title << "!" << endl;
                        Ostream << "Maximal number of tags is " << MAX_TAGS << "." << endl;
                        throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
                    }
                    server.user[i].posts[j].tags[tag_num] = temp.substr(1, temp.length() - 2);
                    tag_num++;
                    if (count == 0) {
                        server.tags[count].tag_content = temp.substr(1, temp.length() - 2);
                        server.tags[count].tag_score = 5;
                        count++;
                    }
                    add_tag(server.tags, count, server.user[i].posts[j].tags[tag_num], 5);
                    server.user[i].posts[j].num_tags = tag_num;
                }

                server.user[i].posts[j].text = temp;

                post >> likenum;
                if(likenum > MAX_LIKES){
                    ostringstream Ostream;
                    Ostream << "Error: Too many likes for post " << server.user[i].posts[j].title << "!" << endl;
                    Ostream << "Maximal number of likes is " << MAX_LIKES << "." << endl;
                    throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
                }
                server.user[i].posts[j].num_likes = likenum;
                post.get(ch);

                find_user(post, server, server.user[i].posts[j].like_users, server.user[i].posts[j].num_likes);

                post >> commentnum;
                if(commentnum > MAX_COMMENTS){
                    ostringstream Ostream;
                    Ostream << "Error: Too many comments for post " << server.user[i].posts[j].title << "!" << endl;
                    Ostream << "Maximal number of comments is " << MAX_COMMENTS << "." << endl;
                    throw Exception_t(CAPACITY_OVERFLOW, Ostream.str());
                }
                server.user[i].posts[j].num_comments = commentnum;
                post.get(ch);

                for (k = 0; k < commentnum; k++) {
                    getline(post, temp);
                    server.user[i].posts[j].comments[k].user = get_user(server, temp);
                    getline(post, temp);
                    server.user[i].posts[j].comments[k].text = temp;
                }

                for (k = 0; k < tag_num; k++) {
                    add_tag(server.tags, count, server.tags[k].tag_content, 3 * commentnum + likenum);
                }
                post.close();
            }
        }



    }
}

User_t *get_user(Server_t& server, const string& name){
    int i;
    for(i = 0; i < server.user_num; i++){
        if(name.compare(server.user[i].username) == 0){
            return &server.user[i];
        }
    }
    return nullptr;
}

void find_user(ifstream& file, Server_t& server, User_t *users[], unsigned int number){
    //get pointers of num to the object such as user[i].followers
    string temp;
    int i;
    for(i = 0; i < number; i++){
        getline(file, temp);
        users[i] = get_user(server, temp);
    }
}

int catch_user(User_t *users, unsigned int num, string& name){
    //find a user's usernumber
    int i;
    for(i = 0; i < num; i++){
        if(name.compare(users[i].username) == 0) return i;
    }
    return -1;
}

int catch_tag(Tag_t *tags, unsigned int num, string& name){
    //find a tag's number in server.tags
    int i;
    for(i = 0; i < num; i++){
        if(name.compare(tags[i].tag_content) == 0) return i;
    }
    return -1;
}

int add_tag(Tag_t tags[], int& num, string& content, int score){
    //add score to the tags of one post
    if(catch_tag(tags, num, content) == -1){
        tags[num].tag_content = content;
        tags[num].tag_score = score;
        num++;
        return 1;
    }
    tags[catch_tag(tags, num, content)].tag_score += score;
    return 0;
}

void follow(User_t *follower, User_t *target){
    follower->following[follower->num_following] = target;
    follower->num_following ++;

    target->follower[target->num_followers] = follower;
    target->num_followers ++;
}

void unfollow(User_t *unfollower, User_t *target){
    unfollower->num_following --;
    remove_user(unfollower->following, unfollower->num_following, target);
    target->num_followers --;
    remove_user(target->follower, target->num_followers, unfollower);
}

void remove_user(User_t *users[], int num, User_t *target){
    int i, n;
    n = catch_user(*users, num, target->username);
    if(n != -1){
        for(i = n; i < num; i++) users[n] = users[n+1];
    }
    users[num - 1] = nullptr;
}

void like(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int num){
    int usernum1 = catch_user(users, server.user_num, username1);
    int usernum2 = catch_user(users, server.user_num, username2);
    int temp;
    string name;

    int i;
    if(users[usernum2].num_posts < num){
        ostringstream Ostream;
        Ostream << "Error: " << username1 << " cannot like post #" << num
        << " of " << username2 << "!" << endl;
        Ostream << username2 << " does not have post #" << num << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }
    else{
        for(i = 0; i < users[usernum2].posts[num].num_likes; i++){
            if(username1.compare(users[usernum2].posts[num].like_users[i]->username) == 0){
                ostringstream Ostream;
                Ostream << "Error: " << username1 << " cannot like post #" << num
                << " of " << username2 << "!" << endl;
                Ostream << username1 << " has already liked post #" << num << "." << endl;
                throw Exception_t(INVALID_LOG, Ostream.str());
            }
        }

        users[usernum2].posts[num].like_users[users[usernum2].posts[num].num_likes] = &users[usernum1];
        users[usernum2].posts[num].num_likes ++;

        for(i = 0; i < users[usernum2].posts[num].num_tags; i++){
            name = users[usernum2].posts[num].tags[i];
            temp = catch_tag(tags, server.tag_num, name);
            tags[temp].tag_score ++;
        }
    }
}

void unlike(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int num){
    int usernum1 = catch_user(users, server.user_num, username1);
    int usernum2 = catch_user(users, server.user_num, username2);
    int i, temp;
    int count = -1;
    string name;
    if(users[usernum2].num_posts < num){
        ostringstream Ostream;
        Ostream << "Error: " << username1 << " cannot unlike post #" << num
                << " of " << username2 << "!" << endl;
        Ostream << username2 << " does not have post #" << num << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }
    else{
        for(i = 0; i < users[usernum2].posts[num].num_likes; i++){
            if(username1.compare(users[usernum2].posts[num].like_users[i]->username) == 0){
                count = i;
            }
        }
        if(count == -1){
            ostringstream Ostream;
            Ostream << "Error: " << username1 << " cannot unlike post #" << num
                    << " of " << username2 << "!" << endl;
            Ostream << username1 << " has not liked post #" << num << " of " <<
            username2 << "." << endl;
            throw Exception_t(INVALID_LOG, Ostream.str());
        }
        remove_user(users[usernum2].posts[num].like_users, count, users[usernum2].posts[num].like_users[count]);
        users[usernum2].posts[num].num_likes --;

        for(i = 0; i < users[usernum2].posts[num].num_tags; i++){
            name = users[usernum2].posts[num].tags[i];
            temp = catch_tag(tags, server.tag_num, name);
            tags[temp].tag_score --;
        }
    }
}

void comment(Server_t& server, User_t *users, Tag_t *tags, string& username1, string &username2, int num, string& text){
    int usernum1 = catch_user(users, server.user_num, username1);
    int usernum2 = catch_user(users, server.user_num, username2);
    int i, temp;
    string name;

    if(users[usernum2].num_posts < num){
        ostringstream Ostream;
        Ostream << "Error: " << username1 << " cannot comment post #" << num
        << " of " << username2 << "!" << endl;
        Ostream << username2 << "does not have post #" << num << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }

    int commentnum = users[usernum2].posts[num].num_comments;
    users[usernum2].posts[num].comments[commentnum].user = &users[usernum1];
    users[usernum2].posts[num].comments[commentnum].text = text;
    users[usernum2].posts[num].num_comments ++;

    for(i = 0; i < users[usernum2].posts[num].num_tags; i++){
        name = users[usernum2].posts[num].tags[i];
        temp = catch_tag(tags, server.tag_num, name);
        tags[temp].tag_score += 3;
    }

}

void uncomment(Server_t& server, User_t *users, Tag_t *tags, string& username1, string& username2, int postnum, int commentnum){
    int usernum1 = catch_user(users, server.user_num, username1);
    int usernum2 = catch_user(users, server.user_num, username2);
    int i, temp1;
    unsigned int temp2;
    string name;

    if(users[usernum2].num_posts < postnum){
        ostringstream Ostream;
        Ostream << "Error: " << username1 << " cannot uncomment comment #" << commentnum
        << " of post #" << postnum << " posted by " << username2 << "!" << endl;
        Ostream << username2 << " does not have post #" << postnum << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }
    else if(users[usernum2].posts[postnum].num_comments < commentnum){
        ostringstream  Ostream;
        Ostream << "Error: " << username1 << " cannot uncomment comment #" << commentnum
        << " of post #" << postnum << " posted by " << username2 << "!" << endl;
        Ostream << "Post #" << postnum << " does not have comment #" << commentnum << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }
    else if(username1.compare(users[usernum2].posts[postnum].comments[commentnum - 1].user->username) != 0){
        ostringstream  Ostream;
        Ostream << "Error: " << username1 << " cannot uncomment comment #" << commentnum
        << " of post #" << postnum << " posted by " << username2 << "!" << endl;
        Ostream << username1 << " is not the owner of comment #" << commentnum << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }
    else{
        for(i = commentnum - 1; i < users[usernum2].posts[postnum].num_comments - 1; i++){
            users[usernum2].posts[postnum].comments[i] = users[usernum2].posts[postnum].comments[i + 1];
        }

        temp2 = users[usernum2].posts[postnum].num_comments - 1;
        users[usernum2].posts[postnum].comments[temp2].text = "";
        users[usernum2].posts[postnum].comments[temp2].user = nullptr;
        users[usernum2].posts[postnum].num_comments --;

        for(i = 0; i < users[usernum2].posts[postnum].num_tags; i++){
            name = users[usernum2].posts[postnum].tags[i];
            temp1 = catch_tag(tags, server.tag_num, name);
            tags[temp1].tag_score -= 3;
        }
    }
}

void post(Server_t& server, User_t *users, Tag_t *tags, string& username, string title, string *tagname, string text, int tagnum){
    int usernum = catch_user(users, server.user_num, username);
    int i;
    unsigned int temp;
    for(i = 0; i < tagnum; i++){
        add_tag(tags, reinterpret_cast<int &>(server.tag_num), tagname[i], 5);
        users[usernum].posts[users[usernum].num_posts + 1].tags[i] = tagname[i];
    }
    temp = users[usernum].num_posts + 1;
    users[usernum].posts[temp].owner = &users[usernum];
    users[usernum].posts[temp].title = title;
    users[usernum].posts[temp].text = text;
    users[usernum].posts[temp].num_likes = 0;
    users[usernum].posts[temp].num_comments = 0;
    users[usernum].posts[temp].num_tags = tagnum;
    users[usernum].num_posts ++;
}

void delete_post(Server_t& server, User_t *users, Tag_t *tags, int num, string& username){
    int usernum = catch_user(users, server.user_num, username);
    int i, temp1;
    unsigned temp2;
    unsigned int likenum, commentnum;
    string name;

    if(users[usernum].num_posts < num){
        ostringstream Ostream;
        Ostream << "Error: " << username << " cannot delete post #" << num << "!" << endl;
        Ostream << username << " does not have post #" << num << "." << endl;
        throw Exception_t(INVALID_LOG, Ostream.str());
    }

    for(i = 0; i < users[usernum].posts[num].num_tags; i++){      //deduct score of tags of post[num]
        name = users[usernum].posts[num].tags[i];
        temp1 = catch_tag(tags, server.tag_num, name);
        likenum = users[usernum].posts[num].num_likes;
        commentnum = users[usernum].posts[num].num_comments;
        tags[temp1].tag_score = tags[temp1].tag_score - 5 - 3 * commentnum - likenum;
    }

    for(i = num; i < users[usernum].num_posts; i++){
        users[usernum].posts[i] = users[usernum].posts[i + 1];
    }
    temp2 = users[usernum].num_posts;
    for(i = 0; i < users[usernum].posts[temp2].num_tags; i++){
        users[usernum].posts[temp2].tags[i] = "";
    }
    for(i = 0; i < users[usernum].posts[temp2].num_likes; i++){
        users[usernum].posts[temp2].like_users[i] = nullptr;
    }
    for(i = 0; i < users[usernum].posts[temp2].num_comments; i++){
        users[usernum].posts[temp2].comments[i].text = "";
        users[usernum].posts[temp2].comments[i].user = nullptr;
    }

    users[usernum].posts[temp2].owner = nullptr;
    users[usernum].posts[temp2].num_tags = 0;
    users[usernum].posts[temp2].num_likes = 0;
    users[usernum].posts[temp2].num_comments = 0;
    users[usernum].posts[temp2].title = "";
    users[usernum].posts[temp2].text = "";
    users[usernum].num_posts --;
}

string rela_judge(User_t *visitor, User_t *target){
    if(visitor->username.compare(target->username) == 0) return "";
    int a = 0, b = 0;  //to judge the relationship, ranging 0 or 1;
    int i;

    for(i = 0; i < target->num_followers; i++){
        if(visitor == target->follower[i]) a = 1;
    }

    for(i = 0; i < visitor->num_followers; i++){
        if(target == visitor->follower[i]) b = 1;
    }

    if(a == 1 && b == 1) return "friend";
    else if(a == 1 && b == 0) return "following";
    else return "stranger";
}

void refresh(Server_t& server, User_t *users, string& username){
    int usernum = catch_user(users, server.user_num, username);
    int i, j;
    for(i = 1; i <= users[usernum].num_posts; i++){
        printPost(users[usernum].posts[i]);
    }
    for(i = 0; i < users[usernum].num_following; i++){
        for(j = 1; j <= users[usernum].following[i]->num_posts; i++){
            printPost(users[usernum].following[i]->posts[j]);
        }
    }
}

bool compare(Tag_t& tag1, Tag_t& tag2){
    unsigned int num1 = tag1.tag_score;
    unsigned int num2 = tag2.tag_score;
    string text1 = tag1.tag_content;
    string text2 = tag2.tag_content;
    int length1 = text1.length();
    int length2 = text2.length();
    int length = max(length1, length2);
    int i;
    if(num1 == num2){
        for(i = 0; i < length; i++){
            if(text1[i] < text2[i]){
                num1 ++;
                break;
            }
            if(text1[i] > text2[i]){
                num2 ++;
                break;
            }
            if(text1[i] == text2[i]) continue;
        }
    }
    return (num1 > num2);
}

void trending(Server_t& server, Tag_t *tags, int num){
    int i;
    sort(tags, tags + server.tag_num + 1, compare);
    if(num >= server.tag_num){
        for(i = 0; i < server.tag_num; i++){
            printTag(tags[i], i + 1);
        }
    }
    else{
        for(i = 0; i < num; i++){
            printTag(tags[i], i + 1);
        }
    }
}

void logfile_process(Server_t& server, User_t *users, Tag_t *tags, string path){
    ifstream file(path);
    if(!file.is_open()){
        ostringstream Ostream;
        Ostream << "Error: Cannot open file " << path << "!" << endl;
        throw Exception_t(FILE_MISSING, Ostream.str());
    }
    string things;
    while(getline(file, things)){
        string username1, username2, command;
        int num1, num2;
        istringstream Istream;

        Istream.str(things);
        Istream >> username1;

        if(username1 == "trending"){
            cout << ">> trending" << endl;
            Istream >> num1;
            trending(server, tags, num1);
            continue;
        }

        Istream >> command;
        cout << ">> " << command << endl;
        try{
            if(command == "follow"){
                Istream >> username2;
                follow(get_user(server, username1), get_user(server, username2));
            }
            else if(command == "unfollow"){
                Istream >> username2;
                unfollow(get_user(server, username1), get_user(server, username2));
            }
            else if(command == "like"){
                Istream >> username2 >> num1;
                like(server, users, tags, username1, username2, num1);
            }
            else if(command == "unlike"){
                Istream >> username2 >> num1;
                unlike(server, users, tags, username1, username2, num1);
            }
            else if(command == "comment"){
                Istream >> username2 >> num1;
                string text;
                getline(file, text);
                comment(server, users, tags, username1, username2, num1, text);
            }
            else if(command == "uncomment"){
                Istream >> username2 >> num1 >> num2;
                uncomment(server, users, tags, username1, username2, num1, num2);
            }
            else if(command == "post"){
                string title, tagline, text;
                string tagname[MAX_TAGS];
                int tagnum = 0;
                getline(file, title);
                while(getline(file, tagline) && tagline[0] == '#'){
                    tagname[tagnum] = tagline.substr(1, tagline.length() - 2);
                    tagnum++;
                }
                text = tagline;
                post(server, users, tags, username1, title, tagname, text, tagnum);
            }
            else if(command == "delete"){
                Istream >> num1;
                delete_post(server, users, tags, num1, username1);
            }
            else if(command == "visit"){
                Istream >> username2;
                int usernum = catch_user(users, server.user_num, username2);
                User_t *user1 = get_user(server, username1);
                User_t *user2 = get_user(server, username2);
                printUser(users[usernum], rela_judge(user1, user2));
            }
            else if(command == "refresh"){
                refresh(server, users, username1);
            }
            else{
                cout << "Unknown error when reading logfile" <<  endl;
            }
        }
        catch(Exception_t& exception){
            cout << exception.error_info;
        }
    }
}


// Printing

void printUser(User_t& user, const string& relationship){
    cout << user.username << endl;
    cout << relationship << endl;
    cout << "Followers: " << user.num_followers
         << "\nFollowing: " << user.num_following << endl;
}


void printPost(Post_t& post){
    cout << post.owner->username << endl;
    cout << post.title << endl;
    cout << post.text << endl;
    cout << "Tags: ";
    for(unsigned int i = 0; i<post.num_tags; ++i){
        cout << post.tags[i] << " ";
    }
    cout << "\nLikes: " << post.num_likes << endl;
    if (post.num_comments > 0){
        cout << "Comments:" << endl;
        for(unsigned int i = 0; i<post.num_comments; ++i){
            cout << post.comments[i].user->username << ": "
                 << post.comments[i].text << endl;
        }
    }
    cout << "- - - - - - - - - - - - - - -" << endl;
}


void printTag(const Tag_t& tag, unsigned int rank){
    cout << rank << " " << tag.tag_content << ": " << tag.tag_score << endl;
}
