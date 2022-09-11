*** Settings ***
Library  SeleniumLibrary
Library  Collections
Library  OperatingSystem

*** Variables ***
${INDEXPATH}         file:///home/artur/Desktop/Testowanie/Lista8/resources/page/index.html
${BROWSER}           Chrome
${EXAMPLE_NAME}      Jan
${EXAMPLE_SURNAME}   Kowalski
${EXAMPLE_EMAIL}     mail@domain.co
${EXAMPLE_COUNTRY}   Poland
${EXAMPLE_MESSAGE}   text message
${ALERT_MESSAGE}     Are you sure?
${GALLERY_IMG_PATH}  //html/body/div//img

*** Keywords ***
Open Browser At Home Page
    Open Browser        ${INDEXPATH}    ${BROWSER}

Recent Tab Name Should Be
    [Arguments]         ${expected}
    Switch Window       NEW
    Title Should Be     ${expected}

Number Of Tabs Should Be
    [Arguments]         ${expected}
    @{windows}          Get Window Handles
    ${numWindows}       Get Length      ${windows}
    Should Be True      ${numWindows} == ${expected}

Wait Until Contact Form Is Loaded
     Wait Until Page Contains Element       id:contact_form

Contact Form Should Be Empty
    Textfield Value Should Be   id:name     ${EMPTY}
    Textfield Value Should Be   id:surname  ${EMPTY}
    Textfield Value Should Be   id:email    ${EMPTY}
    Textarea Value Should Be    id:message  ${EMPTY}

Input Example Data Into Contact Form
    Input Text                  id:name     ${EXAMPLE_NAME}
    Input Text                  id:surname  ${EXAMPLE_SURNAME}
    Input Text                  id:email    ${EXAMPLE_EMAIL}
    Select From List By Label   id:country  ${EXAMPLE_COUNTRY}
    Input Text                  id:message  ${EXAMPLE_MESSAGE}

Submit Contact Form
    Submit Form                 id:contact_form

Number Of Images Should Be
    [Arguments]  ${locator}      ${expected}
    @{images}   Get WebElements  ${locator}
    ${length}   Get Length       ${images}
    Should Be True               ${length} == ${expected}

Log to Console File Name In Attribute       # pass attribute name of objects you want to iterater over (ex. class, src, alt)
    [Arguments]    ${locator}  ${attribute_name}

    @{images}   Get WebElements  ${locator}
    FOR    ${image}    IN    @{images}
        ${dir}  ${file}  Split Path  ${image.get_attribute('${attribute_name}')}
        Log To Console   ${file}
    END

Check If Footer Is Correct
    [Arguments]     ${web}

    Go To   ${INDEXPATH}

    Click Link  link:${web}

    @{footer hrefs}      Get Webelements      //footer/div/a
    @{footer alts}       Get Webelements      //footer/div/a/img
    @{footer}     Create List     ${footer hrefs}  ${footer alts}

    @{hrefs}      Create List
    @{alts}       Create List
    FOR    ${href}  ${alt}    IN ZIP   @{footer}
        Append To List   ${hrefs}   ${href.get_attribute('href')}
        Append To List   ${alts}    ${alt.get_attribute('alt')}
    END

    @{lists}   Create List    ${hrefs}  ${alts}
    FOR    ${page}  ${alt}    IN ZIP    @{lists}
        Go To           ${page}
        ${title}        Get Title
        Should Contain  ${title}  ${alt}  ignore_case=True
    END