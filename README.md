# NoSqlDataBase

In this project we explore how a non SQL database can be constructed and used.

The project:
1. Is implemented in C++ using the facilities of the standard C++ Libraries and Visual Studio 2015.
2. Consists a template class providing key/value in-memory databases where each value consists of:
   Metadata: An item name string
          A category name string
          A text description of the item
          A time-date string recording the date and time the value was written to the database.
          a finite number (possibly zero) of child relationships with other values. Each element of the child relationships collection is the key of another item in the database. Any item holding a key in this collection is the parent of the element accessed by the key.
          An instance of the template type1. This might be a string, a container of a set of values of the same type, or some other collection of data captured in some, perhaps custom, data structure.
3. Supports addition and deletion of key/value pairs.
4. Supports editing of values including the addition and/or deletion of relationships, editing text metadata, and replacing an            existing value's instance with a new instance. Editing of keys is forbidden.
5. Persists database contents to an XML file2. It is intended that this process be reversible, e.g., the database can be restored or      augmented from an existing XML file as well as write its contents out to an XML file.
6. Accepts a positive time interval or number of writes after which the database contents are persisted. This scheduled "save" process    shall continue until cancelled. By default, timed saving is turned off.
5. Supports queries for:
    The value of a specified key.
    The children of a specified key.
    The set of all keys matching a specified pattern which defaults to all keys.
    All keys that contain a specified string in their item name
    All keys that contain a specified string in their category name
    All keys that contain a specified string in their template data section when that makes sense.
    