#include "simulation.h"

int main(int argc, char *argv[]){
    try {
        if (argc < 3) {
            ostringstream Ostream;
            Ostream << "Error: Wrong number of arguments!" << endl;
            Ostream << "Usage: ./p2 <username> <logfile>" << endl;
            throw Exception_t(INVALID_ARGUMENT, Ostream.str());
        }
    }
    catch(const Exception_t& exception){
        cout << exception.error_info;
        return 0;
    }
    Server_t twitter;
    twitter.user_num = 0;
    twitter.tag_num = 0;
    User_t users[20];
    string path1 = argv[1];
    string path2 = argv[2];
    int tagnum = 0;
    int count = 0;
    try {
        init_user(path1, twitter);
        init_post(twitter, twitter.user, twitter.tags, tagnum, count, path1);
        logfile_process(twitter, twitter.user, twitter.tags, path2);
    }
    catch(const Exception_t& exception){
        cout << exception.error_info;
        return 0;
    }

    return 0;

}