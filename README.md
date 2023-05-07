Management of telephone communications

+ For more general context, go to: https://docs.google.com/document/d/1o00jA2p3ONxedkuMI4RT4vgQNcQ36S6PQZL1PpXOtck/edit?usp=sharing


- The libraires required for this mini project:
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <ctype.h>
  
- Adding a structure package (for better optimisation) :
  #pragma pack(1)
 
- Some constants (consider these as configurable):
  #define MAX 500 //THE MAXIMUM NUMBER OF CLIENTS
  #define DEF 64 //A DEFAULT STRING VALUE OF 64 bits (can be 32, 17, 99, ect...)
//Friendly reminder: we're not using memory allocation, contex is given.


Now that the Imports are made & deifinitons declared, let's make a client array structure named "Client". (from line 18 to 27)
A bool enumeration named "Bool" would be good & useful, so let's make one. (from line 30 to 34)

Structures checked!


Let's now make all our prototypes for our functions later (from line 41 to 77)
  
  Starting with ones that returns one character 'char':
    <+> char MainMenuDisplay(char)         : As you guessed, this functions only display a bunch of lines for our main menu then ask the user to input a character &                                                returns the very same input character 
    <+> char ClientManagementMenu(char)    : Same process, different display text.
    <+> char SeekClientMenu(char)          :                .
    <+> char DeleteClientMenu(char)        :                .
    <+> char BillManagementMenu(char)      :                .
                              
                              
  Here are now our main prototypes, the commands that will perform the actions:
    <+> void AddClient(Client[], int)       :  . This one is interesting, depending on our client counter (which starts from 0 since our client is a "Client array")                                                  we're adding anouther client with unique full name. (for example: AddClient(p_Cl, 2) <=> p_Cl[2] = {...})
                                               . Also, each client must have these followings: A first name, a name, a full name, gender (there are only TWO genders), 
                                               age, phone number, ID Card, city & finally an adress.
                                               . Here is an example: p_Cl[0] = { "First Name", "Name", "First Name Name", 27, 'M', 0999999999, AB123456, GitHub City,                                                  Random Adress }
                                           
    <+> void DisplayClient(Client[], int)   :  . Well, this one is almost obvious, it displays a client information, however, in order to execute this function we need                                                the client position. (so the "Client[]" refers to the whole clients list & "int" indicate their position)
                                               . Example: DisplayClient(p_Cl, 3) <=> p_Cl[3] = {...}
                                               . Execution example (a bit raw): Name      : blah
                                                                                Age       : 00
                                                                                Gender    : 'F'
                                                                                Phone num : 0123456789
                                               . Can't be executed without a valid condition
                                           
    <+> void DeleteClient(Client[], int)    :  . Deleting a client is important. Now or later, you ought to remove a client whom aren't now and replace them with new                                                  clients, soo this functions can do the job easily by "removing an element from an array", after all, our client                                                        structure is defined as an array in our main program.
                                               . This function takes as parameters the client array, the position of the client if found & the total numbers of                                                        clients.   
                                               . Can't be executed without a valid condition

    <+> void SameCityClients(Client[], int) :  . If you wanna have a city phone book, we can make a special function that seeks all the clients from that city.
                                               . This function depends on the client array and the total numbers of clients.
                                               . The main procedure i=of this function is a loop that tracks every client and see if the city they live in is the same                                                as the one entered by the user.
 
