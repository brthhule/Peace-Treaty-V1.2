#include "TrainMA.h"

TrainMA::TrainMA()
{

}
TrainMA::TrainMA(Participants* newParticipant)
{
    participant = newParticipant;
    province = participant->getCapital();
}

void TrainMA::TrainMAFunction() {
    participant->showMap();
    int troopCost[5] = { 5, 4, 3, 2, 1 };

    int barracksLevel = province->getBuildingLevel(5);
    std::cout << "Start printing province barracks information: \033[34m\n";
    std::cout << "Province of kingdom " << participant->getKingdomName() << " selected\n";

    std::cout << "Coordinates: ";
    participant->getCapital()->printCoordinates();
    std::cout << "\n\n";
    std::cout << "The barracks level of this province: " << province->getBarracksLevel() << std::endl;

    int troopTier = barracksLevel / 5;
    troopTier += 1;
    if (troopTier > 5)
        troopTier = 5;

    std::cout << "The max tier troop you can train: " << troopTier << ", " << CV::TROOP_NAMES[troopTier - 1] << std::endl;

    int maxTroopsCanTrain = province->getBuildingLevel(5) * 2;

    std::cout << "The max amount of troops you can train at this barracks during this turn (training capacity): " << maxTroopsCanTrain << "\033[0m\n\n";

    int trainTroop;
    std::string trainTroops;
    std::vector<std::string> trainTroopsAV = { "number" };
    char repeat = 'N';
    for (int x = 1; x <= troopTier; x++) {
        trainTroopsAV.push_back(std::to_string(x));
    }


    trainTroop = std::stoi(OF.getInput(false, -1, "What tier troop do you want to train? (1/2/3/4/5) ", trainTroopsAV, false, false));
    char repeatOuterDoLoop = 'N';
    if (trainTroop <= troopTier) {
        int amountOfTroops = 0;
        std::string amountOfTrops = " ";
        std::vector<std::string> amountOfTroopsAV = {};
        for (int x = 0; x <= maxTroopsCanTrain - province->getTroopsTrainedThisTurn(); x++) /*fix this*/
        {
            amountOfTroopsAV.push_back(std::to_string(x));
        }
        do {
            repeatOuterDoLoop = 'N';
            std::cout
                << "How many tier " << troopTier
                << " troops do you want to train (troops trained in this barracks: "
                << province->getTroopsTrainedThisTurn() << "/"
                << maxTroopsCanTrain << ")? ";
            amountOfTroops = std::stoi(OF.getInput(false, -1, "Replacement", amountOfTroopsAV, false, false));

            if (amountOfTroops <= maxTroopsCanTrain -
                province->getTroopsTrainedThisTurn()) {
                std::array<int, 5> requiredResources = { 0, 0, 0, 0, 0 };
                for (int x = 0; x < 5; x++) {
                    requiredResources[0] = troopCost[0] * troopTier;
                    requiredResources[0] *= amountOfTroops;
                }
                std::cout << "The required amount of resources are as follows: \n";
                OF.printResources(requiredResources);

                std::cout << std::endl;
                char repeatProceedWithTraining = 'Y';
                std::vector<char> proceedWithTrainingThree = { 'P', 'S', 'M' };

                do {
                    switch (OF.getOption(6)) {
                    case 'P': {
                        bool trainingIsSuccess = province->subtractCheckResources(requiredResources);

                        if (trainingIsSuccess == false) {
                            std::cout << "Training failed" << std::endl;
                            province->modifyResources(requiredResources, true);
                        }
                        else {
                            std::cout << "Training successful" << std::endl;
                            province->modifySpecificTroop(troopTier - 1, amountOfTroops, true);
                        }
                        break;
                    }
                    case 'S': {
                        province->printResources();
                        break;
                    }
                    case 'M': {
                        repeatProceedWithTraining = 'N';
                        province->addTroopsTrainedThisTurn(amountOfTroops);
                        std::cout << "Returning to menu... " << std::endl;
                    }
                    }
                } while (repeatProceedWithTraining == 'Y');
            }
            else {
                repeatOuterDoLoop = 'Y';
                std::cout << "Amount of troops selected exceeds the training capacity "
                    "of the barracks... please try again"
                    << std::endl;
            }
        } while (repeatOuterDoLoop == 'Y');
    }
}

