#ifndef MENU_H
#define MENU_H

#include "Network.h"

/**
 * @brief Class representing the menu for interacting with the water supply network.
 */
class Menu {
public:

    /* Constructor */
    Menu();

    /* Set Up */
    void setUpMenu(); /**< Sets up the menu. */
    void setUpCustom(); /**< Gets the path to a custom data set. */

    /* Main Menu */
    void mainMenu(bool isLoading); /**< Display the main menu. */
    static void mainMenuOptions(bool isLoading); /**< Display main menu options. */

    /* Basic Service */
    void basicServiceMenu(); /**< Display basic service menu. */
    void basicMaxFlowMenu(); /**< Display basic maximum flow menu. */
    void basicMaxFlowAll(); /**< Calculate maximum flow for all nodes. */
    void basicMaxFlowSingle(); /**< Calculate maximum flow for a single node. */
    void basicWaterDemand(); /**< Calculate water demand deficits. */
    static void basicServiceMenuPrinter(); /**< Print basic service menu options. */
    static void basicMaxFlowMenuPrinter(); /**< Print basic maximum flow menu options. */

    /* Line Failures */
    void lineFailuresMenu(); /**< Display line failures menu. */
    void failuresRemoveStation(); /**< Remove a station due to failure. */
    void failuresRemoveReservoir(); /**< Remove a reservoir due to failure. */
    void failuresRemovePipe(); /**< Remove a pipe due to failure. */
    static void lineFailuresMenuPrinter(); /**< Print line failures menu options. */

    /* Auxiliary Functions */
    /**
     * @brief Receives a node based on user input and type.
     * @tparam NodeType The type of node.
     * @param type The type of node to receive.
     * @param networkID Indicates whether the node belongs to the main network.
     * @return A pointer to the received node.
     */
    template<typename NodeType>
    NodeType* receiveNode(const std::string& type, bool network);
    /**
     * @brief Confirms the user's choice based on the provided flag.
     * @param flag The flag indicating the type of confirmation.
     * @return True if the user confirms, false otherwise.
     */
    static bool confirmChoice(int flag); /**< Confirm a choice. */
    static void pressEnterToReturn(); /**< Prompt user to press Enter to return. */
    /**
     * @brief Gets a filename from the user.
     * @return The filename entered by the user.
     */
    static std::string getFilename(); /**< Get a filename. */

private:

    Network network; /**< Main network. */
    Network subNetwork; /**< Subnetwork. */
    std::string dataPath; /**< Path to data files. */

};

#endif //MENU_H
