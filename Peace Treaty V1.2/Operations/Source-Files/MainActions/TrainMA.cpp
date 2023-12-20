#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Support\Paths.h"
#include PARTICIPANTS_HEADER

using namespace PART;

//Main TrainMA function
void Participants::trainMAMain() {
    //For debugging
    provSPTR province = this->pickYourProvince(1);

    this->showMap();

    //Barracks level determins how 
    int barracksLevel = province->getBuilding(BARRACKS)->getLevel();
    std::cout << "Start printing province barracks information: " << getColor(BLUE);
    std::cout << "Province of kingdom " << getKingdomName() << " selected\n";


    std::cout << "Coordinates: " +
        province->getCoords(COORD::USER) +
        "\n\nThe barracks level of this province: " + 
          std::to_string(barracksLevel) + "\n";

    int troopTier = (barracksLevel / 5) + 1;
    troopTier =  (troopTier > 5) ? troopTier = 5 : troopTier;

    std::cout << "What type of troop do you want to upgrade?\n";
    int troopTypeNum = Input::getOptionPrompt(TRAIN_MA_FUNCTION_UNITS);
    TROOP::TroopTypes type = TroopUnitsBASE::(1);
        

    std::cout << "The max tier troop you can train: " << troopTier << ", " << INF::TROOP_NAMES[troopTier - 1] << std::endl;

    //Change this later
    int maxTroopsCanTrain = barracksLevel * 2;

    std::cout << "The max amount of troops you can train at this barracks during this turn (training capacity): " << maxTroopsCanTrain << "\033[0m\n\n";

    std::vector<std::string> trainTroopsAV = { "number" };
    char repeat = 'N';

    for (int x = 1; x <= troopTier; x++) {
        trainTroopsAV.push_back(std::to_string(x));
    }

    int trainTroop = std::stoi(Input::getInputText("What tier troop do you want to train? (1/2/3/4/5) ", trainTroopsAV));



    char repeatOuterDoLoop = 'N';
    if (trainTroop > troopTier) {
        std::cout << "Invalid troop tier... please try again...\n";
        trainMAMain();
    }
    
    
    int amountOfTroops = 0;
    std::string amountOfTrops = " ";
    std::vector<std::string> amountOfTroopsAV = {};
    /*fix this*/
    for (int x = 0; x <= maxTroopsCanTrain - capitalProvince->getTroopsTrainedThisTurn(); x++) {
        amountOfTroopsAV.push_back(std::to_string(x));
    }

    start:
        repeatOuterDoLoop = 'N';
        std::cout << "How many tier " << troopTier
            << " troops do you want to train (troops trained in this barracks: "
            << capitalProvince->getTroopsTrainedThisTurn() << "/"
            << maxTroopsCanTrain << ")? ";
        
        amountOfTroops = std::stoi(Input::getInputText( "", amountOfTroopsAV));

        if (amountOfTroops > maxTroopsCanTrain - capitalProvince->getTroopsTrainedThisTurn()) {
            repeatOuterDoLoop = 'Y';
            std::cout << "Amount of troops selected exceeds the training capacity "
                "of the barracks... please try again\n";
            goto start;
        }
        

    trainMALoop(troopTier, amountOfTroops);
    
}

void Participants::trainMALoop(int troopTier, int amountOfTroops) {
    //For debugging
    INF::debugFunction("TrainMA, trainMALoop");

    provSPTR capitalProvince = this->getCapitalProvince();

    i5array 
        troopCost = { 5, 4, 3, 2, 1 },
        requiredResources = { 0, 0, 0, 0, 0 };

    for (int x = 0; x < 5; x++) {
        requiredResources[0] = troopCost[0] * troopTier;
        requiredResources[0] *= amountOfTroops;
    }
    std::cout << "The required amount of resources are as follows: \n";
    capitalProvince->printResources(requiredResources);

    std::cout << std::endl;
    char repeatProceedWithTraining = 'Y';
    std::vector<char> proceedWithTrainingThree = { 'P', 'S', 'M' };    
    do {
        switch (Input::getOptionPrompt(TRAIN_MA_FUNCTION).at(0)) {
        case 'P': {
            bool trainingIsSuccess = capitalProvince->subtractCheckResources(requiredResources);

            if (trainingIsSuccess == false) {
                std::cout << "Training failed" << std::endl;
            }
            else {
                std::cout << "Training successful" << std::endl;
                //This is the old troop system. Check this
                capitalProvince->mutateTroop(REGULAR, troopTier, { amountOfTroops }, SINGLE, INCREASE);
            }
            break;
        }
        case 'S': {
            capitalProvince->printResources();
            break;
        }
        case 'M': {
            repeatProceedWithTraining = 'N';
            capitalProvince->addTroopsTrainedThisTurn(amountOfTroops);
            std::cout << "Returning to menu... " << std::endl;
        }
        }
    } while (repeatProceedWithTraining == 'Y');
}

