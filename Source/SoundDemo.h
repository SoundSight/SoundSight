/**
  * This example application is provided with no restrictions on non-commercial use.
  * You are free to modify, distribute, and share this example application, but
  * not to use it commercially or as a source of income.
  */

#ifndef INCLUDE_SOUND_DEMO_H
#define INCLUDE_SOUND_DEMO_H

#include "gsound/GSound.h"

#include "Mesh.h"


using namespace gsound;


class SoundDemo
{
	public:
		
		SoundDemo()
			:	yaw( 0 ),
				pitch( 0 )
		{
		}
		
		Size getNumberOfTriangles() const
		{
			Size result = 0;
			
			for ( Index i = 0; i < scene.getNumberOfObjects(); i++ )
				result += scene.getObject(i)->getMesh()->getNumberOfTriangles();
			
			return result;
		}
		
		
		String name;
		
		SoundScene scene;
		SoundListener listener;
		Real pitch;
		Real yaw;
		
};


SoundSource* createSoundSource( const String& audioFileName, const Vector3& position,
								Real intensity, Real linearAttenuation, Real quadraticAttenuation );


SoundMesh* loadSoundMesh( const Mesh* mesh, const SoundMaterial& material );
SoundMesh* loadSoundMesh( const String& name, const SoundMaterial& material );


const String& getPathToTestData();
void setPathToTestData( const String& newPath );


SoundDemo loadIndoorScene();
SoundDemo loadOutdoorScene();
SoundDemo loadDesertScene();
SoundDemo loadHelicopterScene();
SoundDemo loadCathedralScene();
SoundDemo loadCathedralScene2();

#endif // INCLUDE_SOUND_DEMO_H
