#include <iostream> 
#include <algorithm>

using namespace std;

class IPhone
{
public:
    virtual void Call() = 0;
};

class IPhoto
{
public:
    virtual void TakePhoto() = 0;
};

class IVideo
{
public:
    virtual void MakeVideo() = 0;
};

class IWeb
{
public:
    virtual void BrowseInternet() = 0;
};

class SamsungS20 : public IPhone, IPhoto, IVideo, IWeb
{
public:
    void Call() override { }
    void TakePhoto() override {}
    void MakeVideo() override {}
    void BrowseInternet() override {}
};

class Nokia3310 : public IPhone
{
public:
    void Call() override { }
};

class Camera : public IPhoto, IVideo
{
public:
    void TakePhoto() override { /*нужен только этот метод*/ }
    void MakeVideo() override {}
};

class VideoCamera : public IVideo
{
public:
    void MakeVideo() override {}
};