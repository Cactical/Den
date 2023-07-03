/*

Version 1
Domptero -- by Cactical
Promptero (Version 1.1) but modified for devenv

Made with love :)

Process Tree + Notes on how it should be written (copied from Promptero.hpp + Promptero readme.md file)

The process tree is started from the activate func.
A process is a function that is very important and is needed (and contains things that are needed) for Domptero to work.
The master process is the process that the entire process tree runs in.
The prompt process is the process the prompt runs in.
There should never be a second master process or prompt process.
"directly run" = being run from int main() or from a command.
A func is a function that is run from a process and is usually necessary for Domptero.
A command is a function that the user can ask Domptero to run, it is run from /userinputhandler\.
For the name of the master/prompt process or a func/command, /name\
For a descriptor [descripter] (descripter: [master process], [prompt process], [func], [command])
For a flag, <flag> (flags: <can run x>, <can run yon>, <repeats forever>)
For a note, (note)
For 2 notes, (note) {note}

/master\ [master process] <repeats forever> (runs userprompthandler and x after userprompthandler finishes)
|____/configloader\ [func] loads and saves (maps them to a variable) devenv configuration settings from a devenv configuration file
|____/userprompthandler\ [prompt process] (will never need to be directly run and is automatically run forever)
|    |___/userprompt\ [func] saves input from the user to be used later (can be run whenever a command needs input from user, ex. a command is asking the user to type something to name a file)
|    |___/userinputhandler\ [Func] <can run x> graps input from the user (will never need to be directly run, userprompthandler does that for you) 
|        |___/.command\ [command] <can run x> <can run yon> any command that can be run in devenv, ex. infoccommand (will never need to be directly run, userinputhandler does that for you) {the "." can be the name of any command, ex. version or info}
|        |   |
|        /yon\ [Func] <can throw xerrort1s1 (invalid option)> asks the user "yes" or "no" and saves and refines their input to be used later (can be run whenever a command asks the user a yes or no question ex. if the users want to end devenv or not) {userinputhandler can run yon and devenv can be returned back to userinputhandler once yon is done running}
|        |
|______/x\ [Func] catches xerrors and xoutputs and decides what to with them, ex. telling the user about them (will never need to be directly run, master does that for you)

*/

// #### global variable settings >>>>


/* configdoneswitch var. A switch that controls if a while function will be turned on (false, on state) or not (true, off state).
-------------------------------------------
This var is effectively a switch that controls whether a while function at the start of activate() will be on (it will run) or off (it wont run). The switch will stay on until Den is done loading config settings, Once it is it will turn off and stay off forever. However the setup comand will turn it back on for reconfiguring of the currently loaded devenv configuration settings */
bool configdoneswitch = false;

/* greeterswitch var. A switch that controls if a if function will be turned on (true, on state) or not (false, off state).
-------------------------------------------
This var is effectively a switch that controls whether a if function at the start of master() will be on (it will run) or off (it wont run). The switch will stay on untill the greeter message has been show. Once it has it will turn off and stay off forever. */
bool greeterswitch = true;

/* activateswitch var. A switch that controls if activate() will run when being called (true, on state) or not (false, off state).
-------------------------------------------
This var is effectively a switch that controls whether activate will be on (activate will run) or off (activate wont run). Once activate() is called in the devenv file, control will be passed to Domptero and Domptero wil be in control forever, but you can return control to devenv by making activateswitch false in the devenv file, then control will return to the devenv file. You can also return control to Domptero by simply making activateswitch true and then calling activate() to start up Domptero again. */
bool activateswitch = true;

/* userinput var. Input from the user. 
-------------------------------------------
When userprompt is called, the user types something and whatever they type becomes userinput and userinputhandler decides what to do with userinput. */
std::string userinput;

/* configfilename var. Name of the Denenv configuration file. | devenv configuration setting
-------------------------------------------
Name of the Denenv configuration file, mostly used by Denenv.cpp. */
std::string configfilename = ".devenvconfig";

/* configfile var. Den configuration file. | devenv configuration setting
-------------------------------------------
A file with configuration settings, these settings are mapped to devenv configuration setting variables in the devenv.cpp file. */
std::ifstream configfile(configfilename);

/* configfileoutput var. Output from configfile. 
-------------------------------------------
A string containing stuff in configfile */
std::string configfileoutput;

/* username var. Name of the user. | devenv configuration setting
-------------------------------------------
Name of the user, mostly used by userprompt. */
std::string username;

/* yoninput var. Input that yon uses.
-------------------------------------------
Input yon takes from the user, yon takes the input from userinput and maps it to variable called yoninput */
std::string yoninput;

/* fileline var. Line of a file.
-------------------------------------------
The line of a file fstream is reading. */
int fileline = 1;

/* filecolumn var. Column of a file.
-------------------------------------------
The column of a file fstream is reading. */
int filecolumn = 1;

/* colorrule1 var. sets the primary color (default: blue).
-------------------------------------------
Is a rule that sets the primary color, if 1: blue, if 2: red. */
std::string colorrule1;

/* colorrule2 var. sets the side color (default: cyan).
-------------------------------------------
Is a rule that sets the side color, if 1: cyan, if 2: black. */
std::string colorrule2;

/* colorrule3 var. sets the important color (default: yellow).
-------------------------------------------
Is a rule that sets the important color, if 1: yellow, if 2: white. */
std::string colorrule3;

/* primarycolor var. Is the primary color.
-------------------------------------------
Can either be blue or red. */
std::string primarycolor;

/* sidecolor var. Is the side color.
-------------------------------------------
Can either be cyan or black. */
std::string sidecolor;

/* importantcolor var. Is the important color.
-------------------------------------------
Can either be yellow or white. */
std::string importantcolor;

/* semiimportantcolor var. Is the semiimportant color.
-------------------------------------------
Is green. */
std::string semiimportantcolor = green;

/* errorcolor var. Is the error color.
-------------------------------------------
Is magenta. */
std::string errorcolor = magenta;


// #### x error and output settings >>>>


/* X output: type 1 (command cancelled). 
-------------------------------------------
Is true if: a command was cancelled. */
bool xOUTPUTt1;

/* X error: type 1 (*info*).
-------------------------------------------
Is true if: userinput couldnt be matched with the name of a command.*/
bool xERRORt1;

/* X error: type 1 subtype 1 (*info*).
-------------------------------------------
Is true if: userinput couldnt be matched with the name of a option that a command gave the user.*/
bool xERRORt1s1;

/* X error: type 2 (command cancelled unexpectedly). 
-------------------------------------------
Is true if: a command was cancelled unexpectedly. */
bool xERRORt2;

/* X error: type 2 subtype 1 (command cancelled because the command is not fully developed). 
-------------------------------------------
Is true if: a command was run but it was cancelled because it was not fully developed yet. */
bool xERRORt2s1;


// <<<< x error and outputsettings ####

// <<<< global variable settings ####

// #### function settings >>>>

// #### function declaration >>>>


// WHen modding, only declare a function here if necessary, otherwise declare the function when defining it like normal.

// Basic necessary functions

void activate();
void master();
void configloader();
void userprompthandler();
void userprompt();
void userinputhandler();
void x();
void yon();
__sighandler_t signalhandler();

// commands 

void infocommand();
void versioncommand();
void endcommand();
void configcommand();
void filetoolscommand();


// <<<< function declaration ####

// #### function definition >>>>


// FIXME this just doesnt want to work properly
/* signalhandler func. Handles the sigint signal. (uses signal.h)
-------------------------------------------
If the user does ctrl+c (sigint) this func will start and it will tell them to use the endcommand (not completely working yet). */
void signalhandler(int signum) {
   std::cout << "\nPlease run the end command, \"end.\"" << std::endl;
}

/* activate func. Activates Domptero.
-------------------------------------------
Starts Domptero and calls master(). */
void activate() {
    

    while (activateswitch == true) {
        signal(SIGINT, signalhandler);
        master();
    }    
}

/* master process. Handles userprompthandler and x and makes userprompthandler and x run forever.
-------------------------------------------
The master process, which is the first thing that runs in devenv. Immediately runs userprompthandler and then runs x to catch errors and extra output once userprompthandler finishes. It also runs a devenv configuration settings loader which takes the devenv configuration settings from the default/current configuration file (default: .devenvconfig) and saves them here.*/
void master() {    
    
    // devenv configuration setting loader | Load devenv configuration files from the default devenv configuration file.
    while (configdoneswitch == false) {
        
        std::cout << "Starting config\n";

        configloader();
        
        // Turn off configdoneswitch when loader is done
        configdoneswitch = true;

        std::cout << "Done!\n";

    }

    fileline = 1;

    if (greeterswitch == true){
        
        std::cout << sidecolor << "Welcome to " << primarycolor << "Den" << sidecolor << ". (short for " << primarycolor << "de" << sidecolor << "ve" << primarycolor << "n" << sidecolor << "v)\n";
        std::cout << importantcolor << "Run the info command for info. \n" << white;
        
        // Turn off greeterswitch when greeter is done
        greeterswitch = false;

    }

    userprompthandler();
    x();
    
}


/* configloader func. Loads configuration settings
-------------------------------------------
Loads and saves (maps them to a variable) devenv configuration settings  */
void configloader() {

    while (getline(configfile, configfileoutput)) {
        
        std::cout << "Line " << fileline << " | " << configfileoutput << "\n";

        // If the configfile is empty or contains two asterisks (which means to use the default configuration settings), then set the configuration settings to default.
        if (configfileoutput == "" || configfileoutput == "**") {
        
            username = "NO USERNAME";
            colorrule1 = "1";
            colorrule2 = "1";
            colorrule3 = "1";
            primarycolor = blue;
            sidecolor = cyan;
            importantcolor = yellow;

            configdoneswitch = true;

        } else if (fileline == 1) {
            
            fileline++;
            // Line 1 | the username will be on this line
            // Username Loader | loads the username based on the configuration settings
            username = configfileoutput;

            if (username == "*") {
            
                username = "NO USERNAME";
            
            }       
            
            std::cout << "Done with line 1!\n";

        } else if (fileline == 2) {
            
            fileline++;
            // Line 2 | primary color settings will be on this line, if there is nothing on this line then the default color settings are used.
            // Color Loader 1 | loads the colors based on the configuration settings
            colorrule1 = configfileoutput;

            if (colorrule1 == "1") {
            
                primarycolor = blue;

            } else if (colorrule1 == "2") {
                
                primarycolor = red;
            
            } else if (colorrule1 == "*") {

                primarycolor = blue;
            
            } else {
          
                primarycolor = blue;

            }
            
            std::cout << "Done with line 2!\n";

        } else if (fileline == 3) {

            fileline++;
            // Line 3 | primary color settings will be on this line, if there is nothing on this line then the default color settings are used.
            // Color Loader 2 | loads the colors based on the configuration settings
            colorrule2 = configfileoutput;

            if (colorrule2 == "1") {
           
                sidecolor = cyan;

            } else if (colorrule2 == "2") {
                
                // TODO change to a better color
                sidecolor = black;
            
            } else if (colorrule2 == "*") {
                
                sidecolor = cyan;
            
            } else {
                
                sidecolor = cyan;
            
            }

            std::cout << "Done with line 3!\n";

        } else if (fileline == 4) {
            
            fileline++;
            // Line 4 | primary color settings will be on this line, if there is nothing on this line then the default color settings are used.
            // Color Loader 3 | loads the colors based on the configuration settings
            colorrule3 = configfileoutput;

            if (colorrule3 == "1") {
            
                importantcolor = yellow;

            } else if (colorrule3 == "2") {

                // TODO change to a better color
                importantcolor = white;
        
            } else if (colorrule2 == "*") {
                
                importantcolor = yellow;
            
            } else {
                
                importantcolor = yellow;
            
            }

            std::cout << "Done with line 4!\n";

        } 
    }

}

/* prompt process. Handles userprompt and userinputhandler.
-------------------------------------------
Runs userprompt so the user can tell devenv what to do, then runs userinputhandler so devenv can do something with what the user tells devenv to do.*/
void userprompthandler() {
    userprompt();
    userinputhandler();
}

/* userprompt. Prompt that the user types in. 
-------------------------------------------
Input from this prompt is dumped into the var userinput. */
void userprompt() {
    
    if (username == "NO USERNAME") {

        std::cout << sidecolor << " "; std::getline(std::cin, userinput); std::cout << white;


    } else {
        
        std::cout << sidecolor << username << "  "; std::getline(std::cin, userinput); std::cout << white;

    }

}

/* userinputhandler func. Handles user input.
-------------------------------------------
Sees if userinput matches up with a command name, if so, run the command, if not, change the xERRORt1 var to true to have X throw a error. */
void userinputhandler() {
    if (userinput == "info") {
        infocommand();        
    } else if (userinput == "version") {
        versioncommand();
    }  else if (userinput == "end" || userinput == "q" || userinput == "exit" || userinput == "quit") {
        std::cout << importantcolor << "Are you sure you want to end?";
        yon();
        if (yoninput == "Y") {
            endcommand();
        } else if (yoninput == "N") {
            // Throw "command cancelled" output
            xOUTPUTt1 = true;
        } else {
            
            // Do nothing

        }
    } else if (userinput == "config") {
        configcommand();
    } else if (userinput == "filetools") {
        filetoolscommand();
    } else {
        // Check to see if userinput is empty, if so, dont display a error and just throw the user back into the prompt.
        if (userinput == "") {
            xERRORt1 = false;
        } else {
            // Throw "Invalid command" error
            xERRORt1 = true;
        }
    }
}

/* x func. Error and extra output handler.
-------------------------------------------
Runs everytime userprompthandler is run to catch errors and extra output. If a error is thrown it catches it and displays a error, and then disables the error so it wont show again, if some extra output is thrown then it does the same thing. */
void x() {
    
    std::cout << errorcolor;

    if (xOUTPUTt1 == true) {
        std::cout << "command cancelled. \n";
        xOUTPUTt1 = false;
    } else if (xERRORt1 == true) {
        std::cout << "command does not exist. \n";
        xERRORt1 = false;
    } else if (xERRORt1s1 == true){
        std::cout << "option does not exist. \n";
        xERRORt1s1 = false;
    } else if (xERRORt2 == true) {
        std::cout << "command cancelled unexpectedly. \n";
        xERRORt2 = false;
    } else if (xERRORt2s1 == true) {
        std::cout << "command cancelled. reason: command is not fully developed yet. \n";
        xERRORt2s1 = false;
    }

    std::cout << white;


}


/* yon (yes or no) func. Asks the user yes or no whenever a func or command asks the user a question that can be answered with yes or no. 
-------------------------------------------
Asks user yes or no and runs userprompt so the user can answer, then it takes what the user said and maps it to a var, then refine that var and decide what to do with the refined var. */
void yon() {
    
    std::cout << semiimportantcolor << " (Y/N) \n" << white;
    std::cout << semiimportantcolor << "\\___ " << white;
    userprompt();

    if (userinput == "Y" || userinput == "y" || userinput == "Yes" || userinput == "yes" || userinput == "YES") {
        
        yoninput = "Y";

    } else if (userinput == "N" || userinput == "n" || userinput == "No" || userinput == "no" || userinput == "NO") {

        yoninput = "N";   

    } else {

        xERRORt1s1 = true;

    }

}
/* Info command. Displays info about devenv.
-----------------------------------------------------------
Displays info and help guide. */ 
void infocommand() {
    std::cout << primarycolor;
    std::cout << "\nDen (version 0.1) -- By Cactical.\n";
    std::cout << "Your Den for coding!";
    std::cout << "Den is a developer environment that you can develop code or just edit text files in, basically a mini IDE in the terminal.\n";
    std::cout << "Den is also a mini shell, and you can run its own commands, have your own username (and colors), + more!\n";
    std::cout << "To get Den configured and setup, run the Config command, \"config\".";
    std::cout << "To get started with Den, run the Filetools command, \"filetools\", so you can start creating and editing files in Den,";
    std::cout << "To exit Den, please run the End command, \"end\". \n";
    std::cout << "\n";
    std::cout << "                           COMMANDS\n";
    std::cout << "----------------------------------------------------------\n";
    std::cout << "[^] = Not fully developed\n";
    std::cout << "When running a command, you must type the name of it in lowercase for it to run.\n"; 
    std::cout << "[^] Info - Displays this help guide and info.\n";
    std::cout << "Version - Displays version of Den.\n";
    std::cout << "End - Ends the current Den session. (shortcuts: exit, q, quit) \n";
    std::cout << "[^] Config (v0.1) - Den setup/config command, can create/edit a Den configuration file, load a Den configuration file, and print a Den configuration file or current devenv configuration settings.\n";
    std::cout << "[^] Filetools (v0.1)- Tools for making or modifying a text file (ex. a C++ file or a txt file). \n";
    std::cout << "|\n";
    std::cout << "Filetools Guide [1]: Make a file - Makes a file that can either be a plaintext file (.txt) or a C++ file (.cpp).\n";
    std::cout << "|\n";
    std::cout << "Filetools Guide [2]: [^] Write to a file - Writes text to a file.\n";
    std::cout << "|\n";
    std::cout << "Filetools Guide [3]: [^] Read a file - Displays everything thats in a file line by line.\n";
    std::cout << white;
}

/* Version command. Displays version of devenv.
-------------------------------------------
Shows version of devenv. */
void versioncommand() {
    std::cout << primarycolor << "devenv 0.1\n";
}


/* End command. Ends devenv.
------------------------------------------
What the user will type to end the command they are in, if they arent in one then devenv will end and control will return to devenv.cpp. */
void endcommand() {
    std::cout << importantcolor << "Closing...\n";
    configfile.close();
    activateswitch = false;
    std::cout << "Done!\n";
}

/* Config command. Sets up and configures devenv. 
-------------------------------------------
Sets up and configures devenv based on the Den configuration file. */
void configcommand() {

    // Name of a already made config file | (config command var) 
    std::string configfilename;
    
    std::cout << primarycolor;
    std::cout << "Den config command - 0.1\n";
    std::cout << importantcolor;
    std::cout << "This command is still in heavy development and as of now you can only use it to save your username.\n"; // TODO remove this once config command finished
    std::cout << "This command can make a Den configuration file named \".devenvconfig\" that will contain configuration settings for Den (ex. username, colors, etc.)\n";
    std::cout << "It can also load a existing Den configuration file. Once Den is restarted, the changes will not be saved unless you change the existing file to the default configuration file.\n";
    std::cout << "Den will always load the Den configuration file simply named \".devenvconfig\". This is the default configuration file and can not be changed, but this command can change a Den configuration file to the default.\n";
    std::cout << primarycolor;
    std::cout << "What setup tool would you like to use?\n";
    std::cout << "I - Info on making Den configuration files, editing Den configuration files, etc. [Recommended if this is your first time.]\n";
    std::cout << "|\n";
    std::cout << "1 - Edit/load a existing Den configuration file.\n";
    std::cout << "|\n";
    std::cout << "2 - Create new Den configuration file.\n";
    std::cout << "|\n";
    std::cout << "3 - Read contents of existing Den configuration file or read current Den configuration settings loaded from a existing file.\n";
    std::cout << "|\n";
    std::cout << "C - Cancel command.\n";
    std::cout << "\\___ ";

    userprompt();
    std::cout << primarycolor;

    if (userinput == "C") {
        
        xOUTPUTt1 = true;

    } else if (userinput == "I") {
        
        std::cout << "Info on managing Den configuration.\n";
        std::cout << "-----------------------------------\n";
        std::cout << "To go with all the default settings, simply put \"**\" in the configuration file.";
        std::cout << "Your username will show before the \">\" in the prompt.\n";
        std::cout << "If there is no username, then nothing show before the \">\" in the prompt.\n";
        std::cout << "A color rule can have 2 values, 1 (default value, normal color) or 2 (alternate color).\n";
        std::cout << "Color Rule 1 decides the primary color.\n";
        std::cout << "Color Rule 2 decides the side color.\n";
        std::cout << "Color Rule 3 decides the important color.\n";
        std::cout << "By default (or if all color rule values or 1), primary color = blue, side color = cyan, important color = yellow. ";
        std::cout << "When putting the username in a Den configuration file, put it on the 1st line.\n";
        std::cout << "When putting color rule 1 in a Den configuration file, put it on the 2nd line.\n";
        std::cout << "When putting color rule 2 in a Den configuration file, put it on the 3rd line.\n";
        std::cout << "When putting color rule 3 in a Den configuration file, put it on the 4th line.\n";
        std::cout << "A devenv configuration file would look like so... (the name would be .devenvconfig, or if this was a 2nd Den configuration file, myusernameisthis.devenvconfig)\n";
        std::cout << "-------------------------------------------------------\\/---------\\ \n";
        std::cout << "myusernameisthis                                        | Line 1   |\n";
        std::cout << "1                                                       | Line 2   |\n";
        std::cout << "1                                                       | Line 3   |\n";
        std::cout << "1                                                       | LIne 4   |\n";
        std::cout << "--------------------------------------------------------/\\--------/\n";
        std::cout << "With the above configuration, the username would be \"myusernameisthis\" and all color rules would be the default value, 1.\n";
        std::cout << "If you want all your color rules to be the default values, you dont even have to set them, \nall you have to say is your and Den will set it to the default for you.\n";
        std::cout << "If you have 2 Den configuration files and you want to make the 2nd one (insertusernamehere.devenvconfig) load on startup instead of the default one (.devenvconfig), \nyou can put the name of the 2nd configuration file in the default one and when the default one loads the contents of the 2nd one will load instead of the default one.\n";
    
    } else if (userinput == "1") {
        
        std::cout << "What is the name of the Den configuration file?";
        userprompt();
        configfilename = userinput;
        // This will cause the configuration settings to be loaded again
        configdoneswitch = false;
        
        std::cout << "Done!";
    
    } else if (userinput == "2") {

        std::cout << "Beginning Den configuration/setup...\n";
        std::cout << "First, what is your name? (this will be your username, if this will be your 2nd Den configuration file then the file will be called \"username.devenvconfig\")\n";

        userprompt();
        std::cout << primarycolor;
        username = userinput;

        std::cout << "Username is \"" << username << "\", saving to Den configuration file!\n";

        // TODO make devenv check to see if there is already a .devenvconfig file (maybe using std::filesystem::exists ?) and if there is then have devenv make a new one
        // TODO make devenv check for stuff in the file and tell the user that there is stuff in the file and that its going to make a new devenvconfig file
        std::ofstream configfile(".devenvconfig");
        configfile << username << "\n";
        
        std::cout << "Done!\n";

    } else if (userinput == "3") {
        
        std::cout << "1 - Print existing Den configuration file.\n";
        std::cout << "|\n";
        std::cout << "2 - Print current Den configuration settings.\n";
        std::cout << "\\___ ";
        userprompt();
        std::cout << primarycolor;

        if (userinput == "1") {
            
            std::cout << "Current configuration file = " << configfilename;

            while (getline(configfile, configfileoutput)) {

                std::cout << "Line " << fileline << "| " << configfileoutput;
                fileline++;

            }

        } else if (userinput == "2") {

            std::cout << "Username: " << username << "\n";
            std::cout << "Color Rules" << "\n";
            std::cout << "Color Rule 1: " << colorrule1 << "\n";
            std::cout << "Color Rule 2: " << colorrule2 << "\n";
            std::cout << "Color Rule 3: " << colorrule3 << "\n";
            // TODO find a way to be able to print the color settings
            // the below is commented because its broken
            //std::cout << "Primary Color: " << primarycolor << "\n";
            //std::cout << "Side Color: " << sidecolor << "\n";
            //std::cout << "Important Color: " << importantcolor << "\n";


        } else {
            
            xERRORt1s1 = true;

        }

    } else {
        
        xERRORt1s1 = true;

    }

    
}

/* Filetools command. Tools for managing files. 
-------------------------------------------
Asks user for name of the file they want to create, assigns the input of userprompt to filename and then makes a new file with the name being the value of filename. */
void filetoolscommand() {
    
    // Name of the file | (filetools command var) 
    std::string filename;

    std::cout << "Filetools command - 0.1\n";
    std::cout << "What tool would you like to use? \n";
    std::cout << "1 - Make a file.\n";
    std::cout << "|\n";
    std::cout << "2 - Write to a file.\n";
    std::cout << "|\n";
    std::cout << "3 - Read a file.\n";
    std::cout << "|\n";
    std::cout << "4 - List contents of current directory.\n";
    std::cout << "|\\__4.1 - Include hidden files. \n";
    std::cout << "C - Cancel command.\n";
    std::cout << "\\___ ";
    
    userprompt();
    
    if (userinput == "C") {
        
        xOUTPUTt1 = true;

    } else if (userinput == "1") {
        
        std::cout << "File creation process started, what would you like to name your file?\n";
        std::cout << "\\___ ";
        userprompt();
        
        filename = userinput;
        std::cout << "The name of your file is \"" << filename << "\". What file type do you want this file to be?\n";
        std::cout << "1 - C++ (.cpp).\n";
        std::cout << "|\n";
        std::cout << "2 - Plaintext file (.txt).\n";
                    
        // uncomment everything below once solar development is done
        //std::cout << "|\n";
        //std::cout << "3 - Solar file (.slr).\n";
        std::cout << "\\___ ";
        userprompt();

        if (userinput == "1") {
                
            std::ofstream file(filename + ".cpp");
            file << "#include <iostream> \n";
            file << "\nint main() {\n\n    std::cout << \"C++ file generated by Den.\";\n\n    return(0);\n\n} \n";
            file.close();
            std::cout << "File created!\n";
            
        } else if (userinput == "2") {
                
            std::ofstream file(filename + ".txt");
            file << "text file generated by Den.";
            file.close();
            std::cout << "File created!\n";

        } else {
            
            xERRORt1s1 = true;
            
            // uncomment everything below once solar (programming language in development) development is done
        }//else if (userinput == "3") {
            //std::ofstream file(filename + ".slr");
            //file << "// Solar file generated by Den.";
            //file.close();
            //std::cout << "File created!\n";
        //}
    
    } else if (userinput == "2") {
        
        std::cout << "What is the name of the file (including file extension)?\n";
        std::cout << "\\___ ";
        userprompt();
        filename = userinput;
        xERRORt2s1 = true;
        std::cout << "The name of your file is \"" << filename << "\".\n";

    } else if (userinput == "3") {
        
        std::cout << "What is the name of the file (including file extension)?\n";
        std::cout << "\\___ ";
        userprompt();
        filename = userinput;
        xERRORt2s1 = true;
        std::cout << "The name of your file is \"" << filename << "\".\n";

    
    } else if (userinput == "4") {

        std::cout << "The contents of this current directory are... " << std::endl; std::system("ls"); 
        // TODO replace this system call with a pipe

    } else if (userinput == "4.1") {

        std::cout << "The contents of this current directory (including hidden files) are..." << std::endl; std::system("ls -a");

    
    } else {
       
        xERRORt1s1 = true;
    
    }

}  


// <<<< function definition ####

// <<<< function settings ####








