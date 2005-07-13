#ifndef __FUNCTIONS_H__
#define __FUNCTIONS_H__

#ifndef SCRIPTING_API
#define __suspend
#endif

namespace Scripting
{

/** displays a text file and scrolls it over the screen */
void display_text_file(const std::string& filename);
/**
 * Suspends the script execution for the specified number of seconds
 */
void wait(float seconds) __suspend;
/** translates a give text into the users language (by looking it up in the .po
 * files)
 */
std::string translate(const std::string& text);
/** load a script file and executes it 
 * This is typically used to import functions from external files.
 */
void import(HSQUIRRELVM v, const std::string& filename);

}

#endif
