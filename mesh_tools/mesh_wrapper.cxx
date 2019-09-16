﻿/********************************/
// @author : lyz
// @content: implement of mesh wrapper
// @birth : 2019-09-08
/********************************/
#include "mesh_wrapper.h"
#include "Implementation/mesh_implement.h"
#include "Implementation/stress_field.h"

namespace meshtools {
MeshWrapper::MeshWrapper()
    : impl(new MeshImpl), field(new PrincipalStressField) {}

/**
 *@delete impl,field
 */
MeshWrapper::~MeshWrapper() {
  delete impl;
  delete field;
}

void MeshWrapper::readMesh(std::string filename) { impl->readMesh(filename); }

void MeshWrapper::readStressField(std::string filename) {
  // impl->readStressField(filename);
  if (impl->mesh_loaded) {
    field->readInStress(filename, impl->ovm_mesh);
  } else {
    field->readInStress(filename);
  }
  std::cout << "field : " << field->tensors.size() << std::endl;
}

void MeshWrapper::get_principal_vectors(std::vector<Eigen::Vector3d> &loc,
                                        std::vector<Eigen::Vector3d> &major,
                                        std::vector<Eigen::Vector3d> &middle,
                                        std::vector<Eigen::Vector3d> &minor) {
  field->get_locations(loc);
  field->get_principal_dirs(major, 0);
  field->get_principal_dirs(middle, 1);
  field->get_principal_dirs(minor, 2);
}

void MeshWrapper::singularityLoaction(std::vector<Eigen::Vector3d> &loc,
                                      double tolerance) {
  field->singularityLoaction(loc, tolerance);
}

void MeshWrapper::divideCells(std::vector<int> &split_face_ids,
                              double tolerance) {
  impl->divideCells(field->tensors, split_face_ids, tolerance);
}

void MeshWrapper::request_cell_centers(
    std::vector<Eigen::Vector3d> &retrieve_val) {
  
}

void MeshWrapper::test() {
  // test matching graph

  impl->construct_matching_graph(field->tensors);

  std::vector<int> loop;
  //impl->find_cell_loop(0,loop);
}

void MeshWrapper::saveToOVM(std::string filename) { impl->saveToOVM(filename); }

std::vector<std::string> MeshWrapper::separateFilename(std::string filename) {
  return impl->separateFilename(filename);
}

void MeshWrapper::getFaceData(std::vector<Eigen::Vector3d> &points,
                              std::vector<FaceList<3>> &faces) {
  impl->getFaceData(points, faces);
}

void MeshWrapper::getBoundaryFaceIds(std::vector<int> &faceids_list) {
  impl->getBoundaryFaceIds(faceids_list);
}

void MeshWrapper::getShrinkMesh(
    std::vector<Eigen::Vector3d> &points,
    std::vector<Eigen::Matrix<long long, 3, 1>> &faces) {
  impl->getShrinkMesh(points, faces);
}

std::string MeshWrapper::get_mesh_name() { return impl->mesh_name; }

double MeshWrapper::cellSize() { return impl->cellSize(); }

int MeshWrapper::match_index(int edge_idx) { 
  
  return 0; 
}

size_t MeshWrapper::n_vertices() { return impl->ovm_mesh->n_vertices(); }

size_t MeshWrapper::n_edges() { return impl->ovm_mesh->n_edges(); }

size_t MeshWrapper::n_faces() { return impl->ovm_mesh->n_faces(); }

size_t MeshWrapper::n_cells() { return impl->ovm_mesh->n_cells(); }

} // namespace meshtools