log(DEBUG, "---- LOGGING TEST BEGIN ----")

log(INFO, "Logging stuff as info (won't be recorded unless you turn it on)")
log(DEBUG, "Logging stuff as debug")
log(WARNING, "Logging stuff as warning")
log(ERROR, "EEEEEK!! Logging stuff as error")
log(OFF, "Logging nuffin'")

log(DEBUG, "Testing passing assertion.")
assert(1 == 1)
log(DEBUG, "Testing failed assertion. Won't probably go further.")
assert(1 == 0, "Optional message, in our case 1 is not 0.\n ---- LOGGING TEST REAL END ----")
log(DEBUG, "Here it probably won't go.")

log(DEBUG, "---- LOGGING TEST FAILED ----")
