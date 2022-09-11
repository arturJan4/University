*** Settings ***
Resource  ../resources/pageResources.resource

Test Setup       Open Browser At Home Page              # 1
Test Teardown    Close Browser
*** Test Cases ***
Open home page in a new window
    [documentation]  nowa strona
    [tags]           zad1
    # Pass Execution   stop 1st

    Click Link                 id:new_window_button     # 2

    Number Of Tabs Should Be   2                        # 2 - assert
    Recent Tab Name Should Be  Home

Fill Contact Form
    [documentation]     formularz
    [tags]              zad2
    # Pass Execution      stop 2nd

    Click Link          link:Contact                    # 2

    Wait Until Contact Form Is Loaded                   # 3

    Contact Form Should Be Empty                        # 4

    Input Example Data Into Contact Form                # 5

    Submit Contact Form                                 # 6

    # checks is message matches and confirms
    Alert Should Be Present     ${ALERT_MESSAGE}        # 7

Gallery Test
    [documentation]             galeria
    [tags]                      zad3
    # Pass Execution              stop 3rd

    Click Link                  link:Gallery                          # 2

    Number Of Images Should Be  ${GALLERY_IMG_PATH}  11               # 3

    Log To Console              '\n'
    Log to Console File Name In Attribute  ${GALLERY_IMG_PATH}  src   # 4

Footer Test
    [Documentation]  stopka
    [Tags]  zad4
    # Pass Execution  stop 4nd

    [Template]  Check If Footer Is Correct
    Home
    News
    Contact
    Gallery