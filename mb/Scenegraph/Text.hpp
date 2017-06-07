#ifndef __MB_TEXT__
#define __MB_TEXT__

class Font
{
public:
  struct Glyph
  {
    char symbol;
    float width;
    float height;
    float bearingX;
    float bearingY;
    float advance;
    float uOffset;
    float vOffset;
    float u;
    float v;
  }
  explicit Font( const std::string& fontPath )
  {
    loadGlyphs( fontPath );
  }
  virtual ~Font( void )
  {

  }
  Glyph getGlyph( char c ) { return _glyphs[ c ]; }
private:
  void loadGlyphs( const std::string fileName )
  {
    _glyphs.clear( );

    auto fontAlias = fileName.substr( 0, fileName.find_last_of( "." ) );
    _textureFileName = fontAlias;

    std::ifstream file;
    file.open( mb::FileSystem::getInstance( )->getPathForResource( fileName ) );
    if ( !file.is_open( ) )
    {
      return;
    }

    char buffer[ 1024 ];
    while ( !file.eof( ) )
    {
      input.getline( buffer, 1024 );
      std::stringstream line;
      line << buffer;

      Glyph glyph;
      int symbol;
      line
        >> symbol
        >> glyph.width
        >> glyph.height
        >> glyph.bearingX
        >> glyph.bearingY
        >> glyph.advance
        >> glyph.uOffset
        >> glyph.vOffset
        >> glyph.u
        >> glyph.v;
      glyph.symbol = ( char ) symbol;
      _glyphs[ glyph.symbol ] = glyph;
    }
  }
  std::string _textureFileName;
  std::unordered_map< char, Glyph > _glyphs;
};
class Text: public Geometry
{
public:
  Text( void )
    : _text( "" )
    , _size( 1.0f )
    , _front( nullptr )
    , _primitive( nullptr ) // GL_TRIANGLES
    , _material( new Material( ) )
  {
    addPrimitive( _primitive );
    mb::MaterialComponent* mc = this->getComponent<mb::MaterialComponent>( );
    mc->addMaterial( mb::MaterialPtr( _material ) );
  }
  void setText( const std::string& text )
  {
    _text = text;
    updatePrimitive( );
  }
  void setSize( float size )
  {
    _size = size;
    updatePrimitive( );
  }
  void setFont( Font* font )
  {
    if ( _font == font ) return;
    _font = font;

  }
public:
  virtual void accept( Visitor& v ) override
  {
    visitor.visitText( this );
  }

private:
  void updatePrimitive( void )
  {

  }
  std::string _text;
  float _size;
  Font* _font;
  Primitive* _primitive;
  Material* _material;
};

#endif /* __MB_TEXT__ */
