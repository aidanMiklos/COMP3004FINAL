#ifndef DEFAULTDATALOADER_H
#define DEFAULTDATALOADER_H

class DataStorage;

class DefaultDataLoader
{
public:
    explicit DefaultDataLoader(DataStorage &storage);

    void load();

private:
    DataStorage &storage;   // Figure 1: DefaultDataLoader -> DataStorage
};

#endif // DEFAULTDATALOADER_H
