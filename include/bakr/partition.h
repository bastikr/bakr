#pragma once

#include <array>
#include <vector>

#include <boost/graph/adjacency_list.hpp>

#include "bakr/intpoint.h"


namespace bakr {

using Triangle = std::array<const IntPoint*, 3>;
using Partition = std::vector<const IntPoint*>;

struct PartitionGraphEdge {
  size_t partition_edge0;
  size_t partition_edge1;
};

using TriangleTree = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Triangle, PartitionGraphEdge>;
using PartitionTree = boost::adjacency_list<boost::vecS, boost::vecS, boost::undirectedS, Partition, PartitionGraphEdge>;

} // namespace bakr
