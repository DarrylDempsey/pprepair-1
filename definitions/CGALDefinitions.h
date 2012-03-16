/*
 Copyright (c) 2009-2012, 
 Gustavo Adolfo Ken Arroyo Ohori    g.a.k.arroyoohori@tudelft.nl
 Hugo Ledoux                        h.ledoux@tudelft.nl
 Martijn Meijers                    b.m.meijers@tudelft.nl
 All rights reserved.
 
 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met: 
 
 1. Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer. 
 2. Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following disclaimer in the documentation
 and/or other materials provided with the distribution. 
 
 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// Compile-time options
#define EXACT_CONSTRUCTIONS
#define TRIANGULATION_HIERARCHY

// CGAL kernel
#ifdef EXACT_CONSTRUCTIONS
#include <CGAL/Exact_predicates_exact_constructions_kernel.h>
#else
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#endif

// CGAL values
#include <CGAL/enum.h>

// CGAL classes
#include <CGAL/Polygon_2.h>
#include <CGAL/Polygon_with_holes_2.h>
#include <CGAL/Polygon_set_2.h>
#include <CGAL/Boolean_set_operations_2.h>
#include <CGAL/Triangulation_face_base_with_info_2.h>
#include <CGAL/Constrained_Delaunay_triangulation_2.h>
#include <CGAL/Triangulation_hierarchy_2.h>
#include <CGAL/Constrained_triangulation_plus_2.h>

// Kernel
#ifdef EXACT_CONSTRUCTIONS
typedef CGAL::Exact_predicates_exact_constructions_kernel K;
#else
typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
#endif

// Low level stuff
#ifdef TRIANGULATION_HIERARCHY
typedef CGAL::Triangulation_vertex_base_2<K> TVB;
typedef CGAL::Triangulation_hierarchy_vertex_base_2<TVB> VB;
#else
typedef CGAL::Triangulation_vertex_base_2<K> VB;
#endif
typedef CGAL::Constrained_triangulation_face_base_2<K> FB;
typedef CGAL::Triangulation_face_base_with_info_2<FaceInfo, K, FB> FBWI;
typedef CGAL::Triangulation_data_structure_2<VB, FBWI> TDS;
typedef CGAL::Exact_predicates_tag PT;
typedef CGAL::Exact_intersections_tag IT;
#ifdef EXACT_CONSTRUCTIONS
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, IT> CDT;
#else
typedef CGAL::Constrained_Delaunay_triangulation_2<K, TDS, PT> CDT;
#endif
#ifdef TRIANGULATION_HIERARCHY
typedef CGAL::Triangulation_hierarchy_2<CDT> CDTH;
typedef CGAL::Constrained_triangulation_plus_2<CDTH> Triangulation;
#else
typedef CGAL::Constrained_triangulation_plus_2<CDT> Triangulation;
#endif

// Other types, for easy reading
typedef Triangulation::Point Point;
typedef Triangulation::Segment Segment;
typedef CGAL::Polygon_2<K> Ring;
typedef CGAL::Polygon_with_holes_2<K> Polygon;

// Non CGAL types
typedef std::vector<std::pair<std::vector<Triangulation::Vertex_handle>, std::vector<std::vector<Triangulation::Vertex_handle> > > > TaggingVector;