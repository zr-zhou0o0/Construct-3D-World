/*************************************************************************
���ļ�����                 View.cpp
������ģ���Ŀ�ġ�         �����ඨ��
�������߼����ڡ�           ����� 2024/8/13
�����ļ�¼��               ��
*************************************************************************/

#include <iostream>
#include <iomanip>

#include "Dice.hpp"
#include "../../Controller/Controller.hpp"
#include "View.hpp"

using namespace std;

/*************************************************************************
���������ơ�       View::View
���������ܡ�       ���캯������ʼ��View����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
View::View() : m_Controller(GetInitController()) {
}

/*************************************************************************
���������ơ�       View::~View
���������ܡ�       ��������������View����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
View::~View() {
}

/*************************************************************************
���������ơ�       View::GetInitController
���������ܡ�       ��ȡ��ʼ���Ŀ�����ʵ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         Controller& - ���ؿ�����ʵ��������
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
Controller& View::GetInitController() {
    Controller::InitInstance();
    return Controller::GetInstance();
}

/*************************************************************************
���������ơ�       View::StartDice
���������ܡ�       �������Ӷ�������ʾ��ӭ��Ϣ�������˵�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         ��
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
void View::StartDice() {
    Dice MyDice;
    MyDice.RandomDice();
    std::cout << "Welcome to 3D WORLD CONSTRUCTOR!" << std::endl;
    std::cout << StartMenu() << std::endl;
}

/*************************************************************************
���������ơ�       View::StartMenu
���������ܡ�       ��ʾ�����˵��������û�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - �����˳���Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::StartMenu() {
    while (true) {
        std::cout << "\n--------Start Menu--------" << std::endl;
        std::string Selection;
        std::cout << "Enter [n] to start a new model,  ";
        std::cout << "[o] to open a model, [q] to quit:";
        std::getline(std::cin, Selection);
        if (Selection == "n" || Selection == "N") {
            std::cout << "Starting a new model..." << std::endl;
            std::cout << EditMenu() << std::endl;

        }
        else if (Selection == "o" || Selection == "O") {
            std::cout << OpenModel() << std::endl;
            std::cout << EditMenu() << std::endl;

        }
        else if (Selection == "q" || Selection == "Q") {
            break;
        }
        else {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
    }
    return "Fine. Bye!\n";
}

/*************************************************************************
���������ơ�       View::EditMenu
���������ܡ�       ��ʾ�༭�˵��������û�����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - �����˳���Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::EditMenu() {
    std::cout << "\n --------Edit Model Menu--------\n" << std::endl;
    std::string Selection;

    while (true) {
        std::cout << PrintEditMenu() << std::endl;
        std::cout << "Your selection: " << std::endl;
        getline(cin, Selection);
        try {
            if (Selection == "0" || Selection == "q" || Selection == "Q") {
                break;
            }
            switch (std::stoi(Selection)) {
            case 1 : {
                std::cout << OpenModel() << std::endl;
                break;
            }
            case 2 : {
                std::cout << SaveModel() << std::endl;
                break;
            }
            case 3 : {  // Set Model Name
                while (true) {
                    std::cout << "Enter new model name (q to quit): ";
                    std::string NewName;
                    getline(std::cin, NewName);

                    if (NewName == "q" || NewName == "Q") {
                        break;
                    }

                    Controller::ControllerResult Result
                        = m_Controller.SetModelName(NewName);
                    if (Result == Controller::RES::SUCCESS_SET) {
                        std::cout << "Model name set successfully!" 
                            << std::endl;
                        break;
                    }
                    else if (Result == Controller::RES::INVALID_MODEL_NAME) {
                        std::cout << "Error: "
                            << Controller::Res_Str[static_cast<int>(Result)]
                            << ". Try again." << std::endl;
                    }
                    else {
                        std::cout << "An error occurred. Try again."
                            << std::endl;
                    }
                }
                break;
            }
            case 4 : {
                std::cout << AddMode() << std::endl;
                break;
            }
            case 5 : {
                std::cout << DeleteMode() << std::endl;
                break;
            }
            case 6 : {
                std::cout << ModifyMode() << std::endl;
                break;
            }
            case 7 : {
                std::cout << GetModelInformation() << std::endl;
                break;
            }
            default :
                std::cout << "Invalid selection. Try again." << std::endl;
                break;
            }
        }
        catch (const std::invalid_argument e) {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        catch (const std::out_of_range e) {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        catch (const std::exception e) {
            std::cout << "Unknown error. Try again." << std::endl;
        }
        Selection.clear();
    }

    return "\n--------Close the Model--------\n";
}

/*************************************************************************
���������ơ�       View::PrintEditMenu
���������ܡ�       ��ӡ�༭�˵�ѡ��
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - ���ر༭�˵����ַ�����ʾ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::PrintEditMenu() {
    std::ostringstream Stream;

    Stream << std::string(35, '-') << std::endl;

    Stream << "1   Import Menu" << std::endl;
    Stream << "2   Export Menu" << std::endl;
    Stream << "3   Set Model Name" << std::endl;
    Stream << "4   Add" << std::endl;
    Stream << "5   Delete" << std::endl;
    Stream << "6   Modify" << std::endl;
    Stream << "7   Get Model Information" << std::endl;
    Stream << "0/q Exit Edit Menu" << std::endl;

    std::cout << Stream.str();

    return std::string(35, '-');
}

/*************************************************************************
���������ơ�       View::OpenModel
���������ܡ�       ��ģ���ļ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - ���ش�ģ�͵Ľ����Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::OpenModel() {
    std::cout << "\nOpening a model..." << std::endl;

    while (true) {
        std::cout << "\nPlease enter path to model(q to quit): "
            << std::endl;
        std::string Path;
        std::getline(std::cin, Path);

        if (Path == "q" || Path == "Q") {
            break;
        }

        Controller::ControllerResult Result
            = m_Controller.OpenModelInOBJ(Path);
        if (Result == Controller::RES::SUCCESS_IMPORT) {
            return "Success open.\n";
        }
        else {
            std::cout << "Error: " 
                << Controller::Res_Str[static_cast<int>(Result)]
                << ". Try again." << std::endl;
        }
    }
    return "Import cancelled\n";
}

/*************************************************************************
���������ơ�       View::SaveModel
���������ܡ�       ����ģ���ļ�
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string - ���ر���ģ�͵Ľ����Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::SaveModel() {
    std::cout << "\nSave a model..." << std::endl;
    while (true) {
        std::cout << "Enter file path to save (q to quit): ";
        std::string FilePath;
        getline(std::cin, FilePath);

        if (FilePath == "q" || FilePath == "Q") {
            break;
        }

        Controller::ControllerResult Result
            = m_Controller.SaveModelToOBJ(FilePath);

        if (Result == Controller::RES::SUCCESS_EXPORT) {
            return "Model successfully save.";
        }
        else {
            std::cout << "Error: " 
                << Controller::Res_Str[static_cast<int>(Result)]
                << ". Try again." << std::endl;
        }
    }
    return "Export cancelled\n";
}

/*************************************************************************
���������ơ�       View::AddMode
���������ܡ�       �ṩ��ӵ㡢�ߡ����ģʽѡ�񣬲������û�����ִ����Ӧ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ���ص��༭�˵�����ʾ��Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::AddMode() {
    std::string Selection;
    while (true) {
        std::cout << std::string(20, '-') << std::endl;
        std::cout << "1   Add Point (by coordinates)" << std::endl;
        std::cout << "2   Add Line (by coordinates)" << std::endl;
        std::cout << "3   Add Face (by coordinates)" << std::endl;
        std::cout << "0/q Quit Add Mode" << std::endl;
        std::cout << std::string(20, '-') << std::endl;
        std::cout << "Your selection:";
        getline(cin, Selection);
        if (Selection == "0" || Selection == "q" || Selection == "Q") {
            break;
        }
        else if (Selection == "1") {
            std::cout << AddPoint() << std::endl;
        }
        else if (Selection == "2") {
            while (true) {
                std::vector<std::array<double, 3>> Coordinates(2);
                std::cout << "Enter coordinates for line (q to quit):"
                    << std::endl;
                bool bQuit = false;
                for (int i = 0; i < 2; i++) {
                    for (int j = 0; j < 3; j++) {
                        std::string Input;
                        std::cout << "Point[" << i+1 << "]."
                            << (char)('X' + j) << ": ";
                        getline(std::cin, Input);
                        if (Input == "q" || Input == "Q") {
                            bQuit = true;
                            break;
                        }
                        std::istringstream Stream(Input);
                        if (!(Stream >> Coordinates[i][j])) {
                            std::cout << "Invalid input." << std::endl;
                            i--; // Retry this point
                            break;
                        }
                    }
                    if (bQuit) break;
                }
                if (bQuit) break;
                Controller::ControllerResult Result
                    = m_Controller.AddLine(Coordinates);
                if (Result == Controller::RES::SUCCESS_ADD) {
                    std::cout << "Line added successfully!" << std::endl;
                    break;
                }
                else {
                    std::cout << Controller::Res_Str[static_cast<int>(Result)]
                        << ". Try again." << std::endl;
                }
            }
        }
        else if (Selection == "3") {
            while (true) {
                std::vector<std::array<double, 3>> Coordinates(3);
                std::cout << "Enter coordinates for face (q to quit):"
                    << std::endl;
                bool bQuit = false;
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        std::string Input;
                        std::cout << "Point[" << i+1 << "]."
                            << (char)('X' + j) << ": ";
                        getline(std::cin, Input);
                        if (Input == "q" || Input == "Q") {
                            bQuit = true;
                            break;
                        }
                        std::istringstream Stream(Input);
                        if (!(Stream >> Coordinates[i][j])) {
                            std::cout << "Invalid input. " << std::endl;
                            i--; // Retry this point
                            break;
                        }
                    }
                    if (bQuit) break;
                }
                if (bQuit) break;
                Controller::ControllerResult Result
                    = m_Controller.AddFace(Coordinates);
                if (Result == Controller::RES::SUCCESS_ADD) {
                    std::cout << "Face added successfully!" << std::endl;
                    break;
                }
                else {
                    std::cout << Controller::Res_Str[static_cast<int>(Result)]
                        << ". Try again." << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        Selection.clear();
    }
    return "back to Edit Menu.";
}

/*************************************************************************
���������ơ�       View::AddPoint
���������ܡ�       ���һ���㣬ͨ���û����������
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ��ӵ�Ľ����Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::AddPoint() {
    while (true) {
        std::cout << "Enter point coordinates (x y z)(q to quit): ";
        std::string Input;
        getline(std::cin, Input);

        if (Input == "q" || Input == "Q") {
            break;
        }

        std::istringstream Stream(Input);
        std::array<double, 3> Coordinates;
        if (Stream >> Coordinates[0] 
            >> Coordinates[1] >> Coordinates[2]) {
            Controller::ControllerResult Result
                = m_Controller.AddPoint(Coordinates);

            if (Result == Controller::RES::SUCCESS_ADD) {
                return "success add.";
            }
            else if (Result == Controller::RES::INVALID_INPUT_FORMAT) {
                std::cout << "Error: "
                    << Controller::Res_Str[static_cast<int>(Result)]
                    << ". Try again." << std::endl;
            }
            else {
                std::cout << "An error occurred. Try again."
                    << std::endl;
            }
        }
        else {
            std::cout << "Invalid input format." << std::endl;
            std::cout << "Enter three numbers separated by spaces."
                << std::endl;
        }
    }
    return "add point cancelled";
}

/*************************************************************************
���������ơ�       View::DeleteMode
���������ܡ�       �ṩɾ���ߡ����ģʽѡ�񣬲������û�����ִ����Ӧ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ���ص��༭�˵�����ʾ��Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::DeleteMode() {
    std::string Selection;

    while (Selection != "1" && Selection != "2" && Selection != "0" 
        && Selection != "q" && Selection != "Q") {

        std::cout << std::string(20, '-') << std::endl;
        std::cout << "1   Delete Line (by line index)" << std::endl;
        std::cout << "2   Delete Face (by face index)" << std::endl;
        std::cout << "0/q Quit Delete Mode" << std::endl;
        std::cout << std::string(20, '-') << std::endl;
        std::cout << "Your selection:";
        getline(cin, Selection);

        if (Selection == "0" || Selection == "q" || Selection == "Q") {
            break;
        }
        else if (Selection == "1") {
            while (true) {
                std::cout << "Enter line index to delete(q to quit): ";
                std::string Input;
                getline(std::cin, Input);

                if (Input == "q" || Input == "Q") {
                    break;
                }
                try {
                    unsigned int uLineIndex = std::stoi(Input) - 1;
                    Controller::ControllerResult Result
                        = m_Controller.DeleteLine(uLineIndex);

                    if (Result == Controller::RES::SUCCESS_DELETE) {
                        std::cout << "Line deleted successfully" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Error: "
                            << Controller::Res_Str[static_cast<int>(Result)]
                            << ". Try again." << std::endl;
                    }
                }
                catch (const std::invalid_argument e) {
                    std::cout << "Invalid selection. Try again." << std::endl;
                }
                catch (const std::out_of_range e) {
                    std::cout << "Invalid selection. Try again." << std::endl;
                }
                catch (const std::exception e) {
                    std::cout << "Unknown error. Try again." << std::endl;
                }
            }
        }
        else if (Selection == "2") {
            while (true) {
                std::cout << "Enter face index to delete(q to quit): ";
                std::string Input;
                getline(std::cin, Input);

                if (Input == "q" || Input == "Q") {
                    break;
                }
                try {
                    unsigned int uFaceIndex = std::stoi(Input) - 1;
                    Controller::ControllerResult Result
                        = m_Controller.DeleteFace(uFaceIndex);

                    if (Result == Controller::RES::SUCCESS_DELETE) {
                        std::cout << "Face deleted successfully" << std::endl;
                        break;
                    }
                    else {
                        std::cout << "Error: "
                            << Controller::Res_Str[static_cast<int>(Result)]
                            << ". Try again." << std::endl;
                    }
                }
                catch (const std::invalid_argument e) {
                    std::cout << "Invalid selection. Try again." << std::endl;
                }
                catch (const std::out_of_range e) {
                    std::cout << "Invalid selection. Try again." << std::endl;
                }
                catch (const std::exception e) {
                    std::cout << "Unknown error. Try again." << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        Selection.clear();
    }
    return "back to Edit Menu.";
}

/*************************************************************************
���������ơ�       View::ModifyMode
���������ܡ�       �ṩ�޸��ߡ����ģʽѡ�񣬲������û�����ִ����Ӧ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ���ص��༭�˵�����ʾ��Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::ModifyMode() {
    std::string Selection;
    while (true) {
        std::cout << std::string(20, '-') << "\n1   Modify Line\n" 
            << "2   Modify Face\n" << "0/q Quit Modify Mode\n" 
            << std::string(20, '-') << "\nYour selection: ";
        getline(cin, Selection);
        if (Selection == "0" || Selection == "q" || Selection == "Q") {
            break;
        }
        else if (Selection == "1") {
            while (true) {
                unsigned int uElementIndex, uPointIndex;
                double rX, rY, rZ;
                std::array<double, 3> Coordinates;
                std::cout << "Enter Line index and Point index(q to quit) ";
                std::string Input;
                getline(cin, Input);
                if (Input == "q" || Input == "Q") {
                    break;
                }
                std::istringstream Stream(Input);
                if (Stream >> uElementIndex >> uPointIndex) {
                    uElementIndex--; // Adjusting for 0-based indexing
                    uPointIndex--;
                    std::cout << "Enter new coordinates (X Y Z): ";
                    getline(cin, Input);
                    std::istringstream StreamInner(Input);
                    if (StreamInner >> rX >> rY >> rZ) {
                        Coordinates = { rX, rY, rZ };
                        Controller::RES Res = m_Controller.ModifyLine(
                            uElementIndex, uPointIndex, Coordinates);
                        if (Res == Controller::RES::SUCCESS_MODIFY) {
                            std::cout << "modify successfully" << std::endl;
                            break;
                        }
                        else {
                            std::cout 
                                << Controller::Res_Str[static_cast<int>(Res)]
                                << ". Try again." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Enter format: X Y Z." << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid format." << std::endl;
                }
            }
        }
        else if (Selection == "2") {
            while (true) {
                unsigned int uElementIndex, uPointIndex;
                double rX, rY, rZ;
                std::array<double, 3> Coordinates;
                std::cout << "Enter Face index and Point index(q to quit) ";
                std::string Input;
                getline(cin, Input);
                if (Input == "q" || Input == "Q") {
                    break;
                }
                std::istringstream Stream(Input);
                if (Stream >> uElementIndex >> uPointIndex) {
                    uElementIndex--; 
                    uPointIndex--;
                    std::cout << "Enter new coordinates (X Y Z): ";
                    getline(cin, Input);
                    std::istringstream StreamInner(Input);
                    if (StreamInner >> rX >> rY >> rZ) {
                        Coordinates = { rX, rY, rZ };
                        Controller::RES Res = m_Controller.ModifyFace(
                            uElementIndex, uPointIndex, Coordinates);
                        if (Res == Controller::RES::SUCCESS_MODIFY) {
                            std::cout << "modify successfully" << std::endl;
                            break;
                        }
                        else {
                            std::cout 
                                << Controller::Res_Str[static_cast<int>(Res)]
                                << ". Try again." << std::endl;
                        }
                    }
                    else {
                        std::cout << "Enter format: X Y Z." << std::endl;
                    }
                }
                else {
                    std::cout << "Invalid format." << std::endl;
                }
            }
        }
        else {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        Selection.clear();
    }
    return "back to Edit Menu.";
}

/*************************************************************************
���������ơ�       View::GetModelInformation
���������ܡ�       �ṩ��ȡģ����Ϣ��ģʽѡ�񣬲������û�����ִ����Ӧ����
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ���ص��༭�˵�����ʾ��Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::GetModelInformation() {
    std::string Selection;
    while (true) {
        std::cout << std::string(20, '-') << std::endl;
        std::cout << "1   Get Points in Line" << std::endl;
        std::cout << "2   Get Points in Face" << std::endl;
        std::cout << "3   Get All Model Information" << std::endl;
        std::cout << "0/q Quit Information Menu" << std::endl;
        std::cout << std::string(20, '-') << std::endl;
        std::cout << "Your selection: ";
        getline(cin, Selection);
        if (Selection == "0" || Selection == "q" || Selection == "Q") {
            break;
        }
        else if (Selection == "1") {
            unsigned int uElementIndex;
            std::cout << "Enter Line index: ";
            std::string Input;
            getline(cin, Input);
            std::istringstream Stream(Input);
            if (Stream >> uElementIndex) {
                uElementIndex--; // Adjusting for 0-based indexing
                Controller::ModelInfoInner ModelInfo;
                Controller::RES Result = m_Controller.GetPointsInLine(
                    uElementIndex, ModelInfo);
                if (Result == Controller::RES::SUCCESS_GET) {
                    std::ostringstream StreamInner;
                    StreamInner << std::fixed << std::setprecision(2);
                    StreamInner << "\nPoints:\n";
                    StreamInner << std::setw(10) << "Index" << std::setw(15) 
                        << "X" << std::setw(15) << "Y" << std::setw(15) 
                        << "Z" << "\n";
                    StreamInner << std::string(55, '-') << "\n";
                    for (size_t i = 0; i < ModelInfo.PointSet.size(); ++i) {
                        const auto& Point = ModelInfo.PointSet[i];
                        StreamInner << std::setw(10) 
                            << ModelInfo.PointSetIndex[i] + 1
                            << std::setw(15) << Point[0]
                            << std::setw(15) << Point[1]
                            << std::setw(15) << Point[2] << "\n";
                    }
                    std::cout << StreamInner.str() << std::endl;
                }
                else {
                    std::cout << Controller::Res_Str[static_cast<int>(Result)]
                        << ". Try again." << std::endl;
                }
            }
            else {
                std::cout << "enter a valid Line index." << std::endl;
            }
        }
        else if (Selection == "2") {
            unsigned int uElementIndex;
            std::cout << "Enter Face index: ";
            std::string Input;
            getline(cin, Input);
            std::istringstream Stream(Input);
            if (Stream >> uElementIndex) {
                uElementIndex--; // Adjusting for 0-based indexing
                Controller::ModelInfoInner ModelInfo;
                Controller::RES Result = m_Controller.GetPointsInFace(
                    uElementIndex, ModelInfo);
                if (Result == Controller::RES::SUCCESS_GET) {
                    std::ostringstream Stream2;
                    Stream2 << std::fixed << std::setprecision(2);
                    Stream2 << "\nPoints:\n";
                    Stream2 << std::setw(10) << "Index" << std::setw(15) 
                        << "X" << std::setw(15) << "Y" << std::setw(15) 
                        << "Z" << "\n";
                    Stream2 << std::string(55, '-') << "\n";
                    for (size_t i = 0; i < ModelInfo.PointSet.size(); ++i) {
                        const auto& point = ModelInfo.PointSet[i];
                        Stream2 << std::setw(10) 
                            << ModelInfo.PointSetIndex[i] + 1
                            << std::setw(15) << point[0]
                            << std::setw(15) << point[1]
                            << std::setw(15) << point[2] << "\n";
                    }
                    std::cout << Stream2.str() << std::endl;
                }
                else {
                    std::cout << Controller::Res_Str[static_cast<int>(Result)]
                        << ". Try again." << std::endl;
                }
            }
            else {
                std::cout << "Please enter a valid Face index." << std::endl;
            }
        }
        else if (Selection == "3") {
            std::cout << PrintModel() << std::endl;
        }
        else {
            std::cout << "Invalid selection. Try again." << std::endl;
        }
        Selection.clear();
    }
    return "back to Edit Menu.";
}

/*************************************************************************
���������ơ�       View::PrintModel
���������ܡ�       ��ӡģ�͵���ϸ��Ϣ
����ڲ�����       ��
�����ڲ�����       ��
������ֵ��         std::string ��ӡ�����Ϣ
�������߼����ڡ�   ����� 2024/8/12
�����ļ�¼��       ��
*************************************************************************/
std::string View::PrintModel() {
    Controller::ModelInfoInner ModelInfo;
    Controller::ControllerResult Result = m_Controller.GetModel(ModelInfo);

    std::ostringstream Stream;
    Stream << std::fixed << std::setprecision(2);  

    Stream << "\n" << std::string(30, '+') 
        << "Model State"<< std::string(30, '+') << "\n";

    Stream << "\nModel Name: " << ModelInfo.ModelName << "\n";
    Stream << "Point Count: " << ModelInfo.uPointCount << "\n";
    Stream << "Line Count: " << ModelInfo.uLineCount << "\n";
    Stream << "Face Count: " << ModelInfo.uFaceCount << "\n";

    // Points Table
    Stream << "\nPoints:\n";
    Stream << std::setw(10) << "Index" << std::setw(15) << "X" 
        << std::setw(15) << "Y" << std::setw(15) << "Z" << "\n";
    Stream << std::string(55, '-') << "\n";
    for (size_t i = 0; i < ModelInfo.PointSet.size(); ++i) {
        const auto& Point = ModelInfo.PointSet[i];
        Stream << std::setw(10) << ModelInfo.PointSetIndex[i]+1
            << std::setw(15) << Point[0]
            << std::setw(15) << Point[1]
            << std::setw(15) << Point[2] << "\n";
    }
    Stream << "\n";

    // Lines Table
    Stream << "Lines:\n";
    Stream << std::setw(10) << "Index" << std::setw(15) << "Point1" 
        << std::setw(15) << "Point2" << std::setw(15) << "Length" << "\n";
    Stream << std::string(55, '-') << "\n";
    for (size_t i = 0; i < ModelInfo.LineSet.size(); ++i) {
        const auto& Line = ModelInfo.LineSet[i];
        Stream << std::setw(10) << ModelInfo.LineSetIndex[i]+1
            << std::setw(15) << Line[0]+1
            << std::setw(15) << Line[1]+1
            << std::setw(15) << ModelInfo.LineLengths[i] << "\n";
    }
    Stream << "\n";

    // Faces Table
    Stream << "Faces:\n";
    Stream << std::setw(10) << "Index" << std::setw(15) << "Point1" 
        << std::setw(15) << "Point2" << std::setw(15) << "Point3" 
        << std::setw(15) << "Area" << "\n";
    Stream << std::string(70, '-') << "\n";
    for (size_t i = 0; i < ModelInfo.FaceSet.size(); ++i) {
        const auto& Face = ModelInfo.FaceSet[i];
        Stream << std::setw(10) << ModelInfo.FaceSetIndex[i]+1
            << std::setw(15) << Face[0]+1
            << std::setw(15) << Face[1]+1
            << std::setw(15) << Face[2]+1
            << std::setw(15) << ModelInfo.FaceAreas[i] << "\n";
    }
    Stream << "\n";

    Stream << "Bounding Box Volume: " << ModelInfo.rBoundingBoxVolume << "\n";
    Stream << "Total Line Length: " << ModelInfo.rTotalLineLength << "\n";
    Stream << "Total Face Area: " << ModelInfo.rTotalFaceArea << "\n";

    Stream << "\n" << std::string(33, '+') << " End " 
        << std::string(33, '+') << "\n";

    std::cout << Stream.str() << std::endl;

    return Controller::Res_Str[static_cast<int>(Result)].c_str();
}