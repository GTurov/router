#pragma once

#include "geo.h"

#include <set>
#include <string>
#include <vector>

namespace transport {

using namespace std::literals;

class Stop;

class Route {
public:
    Route(const std::string_view name, const std::vector<Stop*>& stops,
              bool cycled = false);
    void setLength(int meters) {
        length_ = meters;
        curvature_ = (double) length_ / directLength_;
    }
    const std::string& name() const {return name_;}
    const std::vector<Stop*> stops() const {return stops_;}
    bool isCycled() const{return isCycled_;}
    int stopsCount() const {return (isCycled_?stops_.size():stops_.size()*2-1);}
    int uniqueStopCount() const {return uniqueStopCount_;}
    int length() const {return length_;}
    double curvature() const {return curvature_;}
    struct Info {
        std::string name = ""s;
        int stopCount = 0;
        int uniqueStopCount = 0;
        int length = 0;
        double curvature = 1.0;
    };

private:
    std::string name_;
    std::vector<Stop*> stops_;
    bool isCycled_ = false;
    double directLength_ = 0;
    int length_ = 0;
    double curvature_ = 1.0;
    int uniqueStopCount_ = 0;
};

namespace detail {

struct RouteComparator {
    bool operator() (const Route* lhs, const Route* rhs)const ;
};

} // detail

std::ostream& operator<<(std::ostream& out, const Route& route);

std::ostream& operator<<(std::ostream& out, const Route::Info& route);

using RouteSet = std::set<Route*, detail::RouteComparator>;

class Stop {
public:
    Stop(const std::string_view name, const Coordinates place)
        :name_(name), place_(place)  {}
    const Coordinates place() const {return place_;}
    const std::string& name() const {return name_;}
    struct Info {
        std::string name = ""s;
        RouteSet routes;
    };

private:
    std::string name_;
    Coordinates place_;
};

std::ostream& operator<<(std::ostream& out, const Stop& stop);

std::ostream& operator<<(std::ostream& out, const Stop::Info& stop);


} // transport