-- Keep a log of any SQL queries you execute as you solve the mystery.
.schema
SELECT * FROM people;
SELECT * FROM bakery_security_logs WHERE day = 28;
SELECT * FROM crime_scene_reports WHERE day = 28;
SELECT * FROM interviews WHERE day = 28;
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND minute = 23);
SELECT * FROM atm_transactions WHERE day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw';
SELECT * FROM phone_calls WHERE day = 28 AND duration < 60;
SELECT * FROM flights WHERE day = 29 ORDER BY hour ASC;
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15) AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 ORDER BY hour ASC LIMIT 1))) AND phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND duration < 60)
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15) AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 ORDER BY hour ASC LIMIT 1))) AND phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
SELECT * FROM people WHERE license_plate IN (SELECT license_plate FROM bakery_security_logs WHERE day = 28 AND hour = 10 AND activity = 'exit' AND minute > 15 AND minute < 30) AND name IN (SELECT name FROM people WHERE passport_number IN (SELECT passport_number FROM passengers WHERE flight_id IN (SELECT id FROM flights WHERE day = 29 ORDER BY hour ASC LIMIT 1))) AND phone_number IN (SELECT caller FROM phone_calls WHERE day = 28 AND duration < 60) AND id IN (SELECT person_id FROM bank_accounts WHERE account_number IN (SELECT account_number FROM atm_transactions WHERE day = 28 AND atm_location = 'Leggett Street' AND transaction_type = 'withdraw'));
SELECT * FROM people WHERE phone_number IN (SELECT receiver FROM phone_calls WHERE day = 28 AND duration < 60 AND caller = (SELECT phone_number FROM people WHERE name = 'Bruce'));
