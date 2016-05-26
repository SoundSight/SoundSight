/**
  * This example application is provided with no restrictions on non-commercial use.
  * You are free to modify, distribute, and share this example application, but
  * not to use it commercially or as a source of income.
  */

#ifndef INCLUDE_MESH_H
#define INCLUDE_MESH_H


#include "gsound/GSound.h"


using namespace gsound;



class Mesh
{
	public:
		
		Mesh()
		{
		}
		
		
		
		Mesh( const SoundMesh& soundMesh );
		
		
		
		
		static Mesh* loadOBJ( const String& fileName );
		
		
		
		
		class Vertex
		{
			public:
				
				Vertex( const Vector3& newP, const Vector3& newN, const Vector3& newC )
					:	p( newP ),
						n( newN ),
						color( newC )
				{
				}
				
				Vector3 p;
				Vector3 n;
				Vector3 color;
				
		};
		
		class Triangle
		{
			public:
				
				Triangle()
				{
				}
				
				Triangle( UInt32 v1, UInt32 v2, UInt32 v3 )
				{
					v[0] = v1;
					v[1] = v2;
					v[2] = v3;
				}
				
				
				/// Vertex index for the triangle.
				UInt32 v[3];
				
		};
		
		
		void draw();
		
		
		
		ArrayList<Triangle> triangles;
		
		ArrayList<Vertex> vertices;
		
};




#endif // INCLUDE_MESH_H
