#include "C:\Users\Brennen\Source\Repos\brthhule\Peace-Treaty-V1.2\Peace Treaty V1.2\Units\Participants.h"

void Participants::TrainMAFunction() {
    //For debugging
    Provinces* capitalProvince = this->getCapitalProvince();
    INF::debugFunction("TrainMA, TrainMAFunction");

    this->showMap();


    int barracksLevel = capitalProvince->getBuildingLevel(OTHER, BARRACKS, SINGLE)[0];
    std::cout << "Start printing province barracks information: \033[34m\n";
    std::cout << "Province of kingdom " << this->getKingdomName() << " selected\n";

    std::cout << "Coordinates: " +
        capitalProvince->getUserCoordsString() + "\n\nThe barracks level of this province: " + 
          std::to_string(barracksLevel) + "\n";

    int troopTier = barracksLevel / 5;
    troopTier += 1;
    if (troopTier > 5)
        troopTier = 5;

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
        TrainMAFunction();
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
        

    TrainMAFunctionDoWhileLoop(troopTier, amountOfTroops);
    
}

void Participants::TrainMAFunctionDoWhileLoop(int troopTier, int amountOfTroops) {
    //For debugging
    INF::debugFunction("TrainMA, TrainMAFunctionDoWhileLoop");

    Provinces* capitalProvince = this->getCapitalProvince();

    std::array<int, 5> 
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
                capitalProvince->modifyResources(requiredResources, true);
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

