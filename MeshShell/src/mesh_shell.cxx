#include "mesh_shell.h"

MeshShell::MeshShell(VtkWrapper *viewer): _viewer(viewer) { 
	ovm_mesh = new MeshWrapper();
}

MeshShell::~MeshShell() { delete ovm_mesh; }

void MeshShell::drawMesh(int nRenderStyle) {
  std::vector<Eigen::Vector3d> points;
  std::vector<Eigen::Matrix<long long, 3, 1>> faces;

  ovm_mesh->get_face_data(points, faces);

  std::vector<viewtools::Point3d> vtk_points;
  vtk_points.reserve(points.size());
  for (auto i : points) {
    vtk_points.push_back(i.data());
  }
  std::vector<viewtools::Triangle> vtk_faces;
  vtk_faces.reserve(faces.size());
  for (auto j : faces) {
    vtk_faces.push_back(j.data());
  }

  _main_actor = new ActorControler(_viewer->processMesh(vtk_points, vtk_faces));
  mesh_name = ovm_mesh->get_mesh_name();
  /*auto map_item = map_actors.find(mesh_name);
  if (map_item != map_actors.end()) {
    map_item->second = actor;
  } else {
    map_actors.insert(ActorMap::value_type(mesh_name, actor));
  }*/

	// 1 : render edge 2 : render face 3 = 2 + 1
  _main_actor->setRenderSyle(nRenderStyle);
  _main_actor->setColor();

  _viewer->renderActor(_main_actor->get_actor());
}

void MeshShell::readMesh(std::string filename) {
  ovm_mesh->readMesh(filename);
  mesh_loaded = true;
}

void MeshShell::updateMeshRenderStyle(int nRenderStyle) {
  /*if (nRenderStyle == 0) {
    _viewer->removeActor(_main_actor->get_actor());
  } else {
    if (_main_actor->render_status.edge_on == false &&
        _main_actor->render_status.face_on == false)
      _viewer->renderActor(_main_actor->get_actor());
    _main_actor->setRenderSyle(nRenderStyle);
  }*/
  _main_actor->setRenderSyle(nRenderStyle);
  _viewer->refresh();
}