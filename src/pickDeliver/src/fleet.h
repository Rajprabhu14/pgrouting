/*PGR-GNU*****************************************************************

FILE: fleet.h

Copyright (c) 2017 pgRouting developers
Mail: project@pgrouting.org

------

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

 ********************************************************************PGR-GNU*/

#ifndef SRC_PICKDELIVER_SRC_FLEET_H_
#define SRC_PICKDELIVER_SRC_FLEET_H_
#pragma once

#include <deque>
#include <tuple>
#include <string>
#include <vector>

#include "./../../common/src/identifiers.hpp"

#include "./vehicle_pickDeliver.h"
#include "./pgr_messages.h"
#include "./pd_problem.h"


namespace pgrouting {


namespace tsp {
class Dmatrix;
}
namespace vrp {

class Pgr_pickDeliver;
class PD_Orders;

class Fleet : public PD_problem {
     //typedef std::vector<Vehicle_pickDeliver> Trucks;

 public:
     // static Pgr_pickDeliver* problem;
     typedef std::vector<Vehicle_pickDeliver>::iterator iterator;
      std::vector<Vehicle_pickDeliver> m_trucks;

 protected:
     Identifiers<size_t> used;
     Identifiers<size_t> un_used;



 public:
     /* @brief constructor
      *
      * @params [in] p_problem \t pointer to problem
      *
      */
     Fleet() = default;

     Fleet(const std::vector<Vehicle_t> &vehicles);

#if 0
     Fleet(const std::vector<Vehicle_t> &vehicles,
             const pgrouting::tsp::Dmatrix &cost_matrix);
#endif
     Fleet(const Fleet &fleet);

     /* TODO move code to .cpp */
     Fleet& operator=(const Fleet &fleet) {
         m_trucks = fleet.m_trucks;
         used = fleet.used;
         un_used = fleet.un_used;
         return *this;
    }

     
#if 0
     /* @brief build fleet for matrix version
      *
      * @params [in] vehicles 
      * @params [in] cost_matrix
      *
      */
     void build_fleet(
             std::vector<Vehicle_t> vehicles,
             const pgrouting::tsp::Dmatrix &cost_matrix);
#endif

     /* @brief build fleet for eucledian version
      *
      * @params [in] vehicles 
      *
      */
     bool build_fleet(
             std::vector<Vehicle_t> vehicles);


     void set_compatibles(const PD_Orders &orders);

     bool is_fleet_ok() const;
     bool is_order_ok(const Order &order) const;

     Vehicle_pickDeliver get_truck();
     void release_truck(size_t id);
     Vehicle_pickDeliver get_truck(size_t order);
     Vehicle_pickDeliver get_truck(const Order order);

     //! name vector like functions
     //@{
     size_t size() const {return m_trucks.size();}
     Vehicle_pickDeliver& operator[](size_t i);
     iterator begin() {return m_trucks.begin();}
     iterator end() {return m_trucks.end();}

     //@}

     friend std::ostream& operator << (std::ostream &log, const Fleet &v);

};


}  //  namespace vrp
}  //  namespace pgrouting

#endif  // SRC_PICKDELIVER_SRC_FLEET_H_
