/*
 * AccountController -- implementation
 *
 * TODO:
 *   - identify(): look the name or username up through CafeDataStore and
 *     remember the username. [D1 p.2-3 Feature 1]
 *   - logout(): clear the remembered username. [D1 p.3 Feature 1]
 */

#include "accountcontroller.h"

#include "cafedatastore.h"

AccountController::AccountController()
    : store(CafeDataStore::instance())
{
}
