/**
  * This example application is provided with no restrictions on non-commercial use.
  * You are free to modify, distribute, and share this example application, but
  * not to use it commercially or as a source of income.
  */

#include "SoundDemo.h"

extern SoundPropagator* propagator;
extern SoundPlayer* player;

String pathToTestData;



const String& getPathToTestData()
{
	return pathToTestData;
}




void setPathToTestData( const String& newPath )
{
	pathToTestData = newPath;
}



//##########################################################################################
//##########################################################################################
//############		
//############		Sound Source Creation Function
//############		
//##########################################################################################
//##########################################################################################




SoundSource* createSoundSource( const String& audioFileName, const Vector3& position,
								Real intensity, Real linearAttenuation, Real quadraticAttenuation )
{
	SoundSource* source = new SoundSource( position );
	source->setIntensity( intensity );
	source->setDistanceAttenuation( SoundDistanceAttenuation( 1, linearAttenuation, quadraticAttenuation ) );
	source->setReverbDistanceAttenuation( SoundDistanceAttenuation( 1, 0.5, 0 ) );
	
	WaveDecoder* decoder = new WaveDecoder( pathToTestData + audioFileName );
//	WaveDecoder* decoder = new WaveDecoder( String("Data/acoustics.wav"));
	player = new SoundPlayer( decoder );
	
	player->setIsPlaying( true );
	player->setIsLooping( true );
	
	source->setSoundInput( player );
	
		
	
	return source;
}




//##########################################################################################
//##########################################################################################
//############		
//############		Mesh Loading Functions
//############		
//##########################################################################################
//##########################################################################################




SoundMesh* loadSoundMesh( const Mesh* mesh, const SoundMaterial& material )
{
	ArrayList<SoundVertex> vertices( mesh->vertices.getSize() );
	ArrayList<SoundTriangle> triangles( mesh->triangles.getSize() );
	
	for ( Index i = 0; i < mesh->vertices.getSize(); i++ )
		vertices.add( mesh->vertices[i].p );
	
	for ( Index i = 0; i < mesh->triangles.getSize(); i++ )
		triangles.add( SoundTriangle( mesh->triangles[i].v[0], mesh->triangles[i].v[1], mesh->triangles[i].v[2], 0 ) );
	
	ArrayList<SoundMaterial> materials;
	materials.add( material );
	
	SoundMesh* soundMesh = new SoundMesh( vertices, triangles, materials, SoundMeshPreprocessor(0.001, 0.99) );
	
	soundMesh->setUserData( &mesh );
	
	return soundMesh;
}




SoundMesh* loadSoundMesh( const String& name )
{
	SoundMesh* soundMesh = SoundMeshSerializer().deserialize( pathToTestData + name );
	
	if ( soundMesh == NULL )
	{
		printf("\nError loading SoundMesh file: %s",name.c_str());
		return NULL;
	}
	
	soundMesh->setUserData( new Mesh(*soundMesh) );
	
	return soundMesh;
}




//##########################################################################################
//##########################################################################################
//############		
//############		Demo Scene Loading Functions
//############		
//##########################################################################################
//##########################################################################################




SoundDemo loadIndoorScene()
{
	SoundDemo demo;
	
	demo.name = "Simple Indoor";
	
	SoundObject* world = new SoundObject( loadSoundMesh("indoor.sm") );
	
	// Scale the mesh so that 1 unit == 1 meter.
	world->setScale( 0.07 );
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 0, 1.607064, 0 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//source->setIntensity(0);
	//propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( -0.027009, 1.752445, 5.05597 ) );
	demo.yaw = 0;
	demo.pitch = 0;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}




SoundDemo loadOutdoorScene()
{
	SoundDemo demo;
	
	demo.name = "Outdoor 1";
	
	SoundObject* world = new SoundObject( loadSoundMesh("outdoor.sm") );
	
	// Scale the mesh so that 1 unit == 1 meter.
	world->setScale( 0.2 );
	world->setPosition( Vector3( 0, -10, 0 ) );
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 0, 1.607064, 0 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//	source->setIntensity(0);
	//propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( -15.441011, -1.432085, -2.838621 ) );
	demo.yaw = 98;
	demo.pitch = 0;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}



SoundDemo loadDesertScene()
{
	SoundDemo demo;
	
	demo.name = "Outdoor 2";
	
	SoundObject* world = new SoundObject( loadSoundMesh("desert.sm") );
	
	// Scale the mesh so that 1 unit == 1 meter.
	world->setScale( 2 );
	world->setPosition( Vector3( 0, 0, 0 ) );
	world->setOrientation( Matrix3::rotationXDegrees(90) );
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 0, 5, 0 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//	source->setIntensity(0);
	//propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( 13.422318, 1.282639, -10.604598 ) );
	demo.yaw = 215;
	demo.pitch = 0;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}




SoundDemo loadHelicopterScene()
{
	SoundDemo demo;
	
	demo.name = "Simple Outdoor";
	
	SoundObject* world = new SoundObject( loadSoundMesh("simple.sm") );
	
	// Scale the mesh so that 1 unit == 1 meter.
	world->setOrientation( Matrix3::rotationXDegrees(90) );
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 5.891033, 5.413926, -3.031476 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//	source->setIntensity(0);
	//	propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( 12.979268, 2.962096, 8.773490 ) );
	demo.yaw = -42;
	demo.pitch = 8;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}



SoundDemo loadCathedralScene()
{
	SoundDemo demo;
	
	demo.name = "Cathedral";
	
	SoundObject* world = new SoundObject( loadSoundMesh("sibenik.sm") );
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 0, 1.607064, 0 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//	source->setIntensity(0);
	//propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( 22.620913, 1.628667, 0.363413 ) );
	demo.yaw = -90;
	demo.pitch = 0;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}


SoundDemo loadCathedralScene2()
{
	SoundDemo demo;
	
	demo.name = "Cathedral2";
	
	SoundObject* world = new SoundObject( loadSoundMesh("sibenik.sm") );

	FrequencyResponse f1(0.98, 0.98, 0.98, 0.97, 0.96, 0.95, 0.93, 0.92); 
	FrequencyResponse f0(0, 0, 0, 0, 0, 0, 0, 0); 
	SoundMaterial newmat(f1,f0,f0);
	
	//	world->getMesh()->getMaterial(0).setReflectionAttenuation(

	world->getMesh()->setMaterial(0,newmat);

//	int p = soundMesh->getNumberOfMaterials(); //HDK TEST
//	gsound::SoundMaterial pp = world->getMesh()->getMaterial(0);
//	pp.
	
	demo.scene.addObject( world );
	
	//**************************************************************************************
	
	SoundSource* source = createSoundSource( "onesec.wav", Vector3( 0, 1.607064, 0 ), 5, 2, 0 );
	demo.scene.addSource( source );
	//	source->setIntensity(0);
	//propagator->setDirectSoundIsEnabled( false );
	//**************************************************************************************
	
	demo.listener.setPosition( Vector3( 22.620913, 1.628667, 0.363413 ) );
	demo.yaw = -90;
	demo.pitch = 0;
	demo.listener.setOrientation( Matrix3::rotationYDegrees(demo.yaw)*Matrix3::rotationXDegrees(demo.pitch) );
	
	return demo;
}


