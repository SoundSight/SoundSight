/**
  * This example application is provided with no restrictions on non-commercial use.
  * You are free to modify, distribute, and share this example application, but
  * not to use it commercially or as a source of income.
  */

#include "Mesh.h"


#if defined(GSOUND_PLATFORM_APPLE)
	#include <GLUT/glut.h>
#elif defined(GSOUND_PLATFORM_WINDOWS)
	#include "GL/glut.h"
#endif



Mesh:: Mesh( const SoundMesh& soundMesh )
{
	Vector3 light1Direction( 0.25, -0.25, 0.5 );
	light1Direction = light1Direction.normalize();
	Vector3 light1Color( 1.0, 1.0, 1.0 );
	
	Vector3 light2Direction( -0.5, -0.25, -0.25 );
	light2Direction = light2Direction.normalize();
	Vector3 light2Color( 1.0, 1.0, 0.5 );
	
	Vector3 surfaceColor( 1.0, 1.0, 1.0 );
	
	for ( Index i = 0; i < soundMesh.getNumberOfTriangles(); i++ )
	{
		SoundTriangle triangle = soundMesh.getTriangle(i);
		
		Vector3 v1 = soundMesh.getVertex(triangle.v[0]);
		Vector3 v2 = soundMesh.getVertex(triangle.v[1]);
		Vector3 v3 = soundMesh.getVertex(triangle.v[2]);
		
		Vector3 normal = -math::cross( v2 - v1, v3 - v1 ).normalize();
		
		Vector3 color = surfaceColor*light1Color*(math::clamp( math::dot( normal, light1Direction ), 0.1f, 1.0f ) ) + 
						surfaceColor*light2Color*(math::clamp( math::dot( normal, light2Direction ), 0.1f, 1.0f ) );
		
		vertices.add( Vertex( v1, normal, color*math::clamp( math::abs( math::dot( v1.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		vertices.add( Vertex( v2, normal, color*math::clamp( math::abs( math::dot( v2.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		vertices.add( Vertex( v3, normal, color*math::clamp( math::abs( math::dot( v3.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		
		triangles.add( Triangle( i*3 + 0, i*3 + 1, i*3 + 2 ) );
	}
}





Mesh* Mesh:: loadOBJ( const String& fileName )
{
	FILE* file = fopen( fileName.c_str(), "r" );
	
	GSOUND_ASSERT_MESSAGE( file != NULL, "Error while loading OBJ file." );
	
	Mesh* mesh = new Mesh();
	
	ArrayList<Vector3> vertices;
	
	while ( !feof(file) )
	{
		char lineType = '\0';
		
		fscanf( file, "%c ", &lineType );
		
		if ( lineType == 'v' )
		{
			Vector3 vertex;
			fscanf( file, "%f %f %f\n", &vertex.x, &vertex.z, &vertex.y );
			
			vertices.add( vertex );
		}
		else if ( lineType == 'f' )
		{
			Triangle triangle;
			
			fscanf( file, "%d %d %d\n", &triangle.v[0], &triangle.v[1], &triangle.v[2] );
			
			triangle.v[0]--;
			triangle.v[1]--;
			triangle.v[2]--;
			
			mesh->triangles.add( triangle );
		}
		else
		{
			fscanf( file, "%*s\n" );
			continue;
		}
	}
	
	fclose( file );
	
	Vector3 light1Direction( 0.25, -0.25, 0.5 );
	light1Direction = light1Direction.normalize();
	Vector3 light1Color( 1.0, 1.0, 1.0 );
	
	Vector3 light2Direction( -0.5, -0.25, -0.25 );
	light2Direction = light2Direction.normalize();
	Vector3 light2Color( 1.0, 1.0, 0.5 );
	
	Vector3 surfaceColor( 1.0, 1.0, 1.0 );
	
	for ( Index i = 0; i < mesh->triangles.getSize(); i++ )
	{
		Vector3 v1 = vertices[mesh->triangles[i].v[0]];
		Vector3 v2 = vertices[mesh->triangles[i].v[1]];
		Vector3 v3 = vertices[mesh->triangles[i].v[2]];
		
		Vector3 normal = -math::cross( v2 - v1, v3 - v1 ).normalize();
		
		Vector3 color = surfaceColor*light1Color*(math::clamp( math::dot( normal, light1Direction ), 0.1f, 1.0f ) ) + 
						surfaceColor*light2Color*(math::clamp( math::dot( normal, light2Direction ), 0.1f, 1.0f ) );
		
		mesh->vertices.add( Vertex( v1, normal, color*math::clamp( math::abs( math::dot( v1.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		mesh->vertices.add( Vertex( v2, normal, color*math::clamp( math::abs( math::dot( v2.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		mesh->vertices.add( Vertex( v3, normal, color*math::clamp( math::abs( math::dot( v3.normalize(), light1Direction ) ), 0.7f, 1.0f ) ) );
		
		mesh->triangles[i].v[0] = i*3 + 0;
		mesh->triangles[i].v[1] = i*3 + 1;
		mesh->triangles[i].v[2] = i*3 + 2;
	}
	
	return mesh;
}



void Mesh:: draw()
{
	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnableClientState( GL_COLOR_ARRAY );
	glEnableClientState( GL_INDEX_ARRAY );
	
	glVertexPointer( 3, GL_FLOAT, sizeof(Vertex), vertices.getArrayPointer() );
	glNormalPointer( GL_FLOAT, sizeof(Vertex), &vertices[0].n );
	glColorPointer( 3, GL_FLOAT, sizeof(Vertex), &vertices[0].color );
	
	glDrawElements( GL_TRIANGLES, (GLsizei)triangles.getSize()*3, GL_UNSIGNED_INT, triangles.getArrayPointer() );
}



