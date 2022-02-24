#include "file.h"

void direct(std::string filename){
    DIR *directory;   // creating pointer of type dirent
    struct dirent *x;   // pointer represent directory stream 
    std::string path = "/";
    if ((directory= opendir (path.c_str())) != NULL)//check if directory is open 
    {
        const size_t nthreads = std::thread::hardware_concurrency(); // amount of available threads
        std::vector<std::thread> threads(nthreads);// vector of threads
        int t =0;
        while ((x = readdir (directory)) != NULL) {
  
            if (!x->d_name || x->d_name[0] == '.') continue;
            
            if(x->d_type == DT_DIR)
            {
            
                threads[t]=std::thread(search, path+x->d_name, filename);    
                threads[t].join(); 
                t++;
                if (t == nthreads ) t=0;

            }

        }

    }
 
    closedir (directory); //close directory

}


void search(const std::string &path, std::string filename)
{ 
    DIR *directory;
    struct dirent *x;   
    if ((directory= opendir (path.c_str())) != NULL) 
    {      
        while ((x = readdir (directory)) != NULL) 
        {
            if (!x->d_name || x->d_name[0] == '.') continue;
            if(x->d_type == DT_DIR)
            {
                search(path+"/"+x->d_name, filename);

            } else if(filename == x->d_name)
            {
                std::cout << path << "/" << x->d_name << std::endl;
                break;
            }

        }

    }
 
    closedir (directory); //close directory....
  
}
