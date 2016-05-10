/*
 * Eric Bachmeier
 * ebachme@uwo.ca
 * Assignment 1
 * CS3357 Computer Networks I
 * Western University
 * Professor Jeff Shantz
 * October 12, 2015
 * hdb.h is the header file with function prototypes for hdb.c
 */

#ifndef HDB_H
#define HDB_H

#include <stdbool.h>

// Connection to the Hooli database
typedef void* hdb_connection;

// A record stored in the Hooli database
typedef struct hdb_record {
  char* username;
  char* filename;
  char* checksum;
  struct hdb_record* next;
} hdb_record;

// Connect to the specified Hooli database server, returning the initialized
// connection.
hdb_connection* hdb_connect(const char* server);

// Disconnect from the Hooli database server.
void hdb_disconnect(hdb_connection* con);

// Store a file record in the Hooli database.
void hdb_store_file(hdb_connection* con, hdb_record* record);

// Remove a file record from the Hooli database.
int hdb_remove_file(hdb_connection* con, const char* username, const char* filename);

// If the specified file is found in the Hooli database, return its checksum.
// Otherwise, return NULL.
char* hdb_file_checksum(hdb_connection* con, const char* username, const char* filename);

// Get the number of files stored in the Hooli database for the specified user.
int hdb_file_count(hdb_connection* con, const char* username);

// Return a Boolean value indicating whether or not the specified user exists
// in the Hooli database
bool hdb_user_exists(hdb_connection* con, const char* username);

// Return a Boolean value indicating whether or not the specified file exists
// in the Hooli database
bool hdb_file_exists(hdb_connection* con, const char* username, const char* filename);

// Return a linked list of all of the specified user's file records stored in the
// Hooli database
hdb_record* hdb_user_files(hdb_connection* con, const char* username);

// Free the linked list returned by hdb_user_files()
void hdb_free_result(hdb_record* record);

// Function to authenticate a user by password and output a 16-byte token of their password.
char* hdb_authenticate(hdb_connection* con, const char* username, const char* password);

// Function to verify the 16-byte token, returns the username of the valid token or NULL if it is not valid
char* hdb_verify_token(hdb_connection* con, const char* token);

// Delete the specifid user and all of his/her file records from the Hooli
// database.
int hdb_delete_user(hdb_connection* con, const char* username);

#endif
