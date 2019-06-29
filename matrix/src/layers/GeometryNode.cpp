#include <GeometryNode.h>

namespace MX
{
  GeometryNode::GeometryNode(const std::string &name)
    : Node(name)
  {
    m_textures = std::shared_ptr<TextureProfile>(new TextureProfile());
  }

  void GeometryNode::upload_uniforms()
  {
    Node::upload_uniforms();

    if (m_textures->diffuse != nullptr)
    {
      m_textures->diffuse->use(0);
      m_Shader->setInt("material.diffuse_texture1", 0);
    }

    if (m_textures->specular != nullptr)
    {
      m_textures->specular->use(1);
      m_Shader->setInt("material.specular_texture1", 1);
    }
    
    if (m_textures->normal != nullptr)
    {
      m_textures->normal->use(2);
      m_Shader->setInt("material.normal_texture1", 2);
    }
    
    if (m_textures->bump != nullptr)
    {
      m_textures->bump->use(3);
      m_Shader->setInt("material.bump_texture1", 3);
    }
    
    if (m_textures->height != nullptr)
    {
      m_textures->height->use(4);
      m_Shader->setInt("material.height_texture1", 4);
    }

    m_Shader->setfVec3("material.ambient", m_material.ambient);
    m_Shader->setfVec3("material.diffuse", m_material.diffuse);
    m_Shader->setfVec3("material.specular", m_material.specular);

    m_Shader->setFloat("material.shininess", m_material.shininess);

    if (m_Model != nullptr)
      m_Model->render(std::static_pointer_cast<MX_SHADER>(m_Shader));
  }

  void GeometryNode::setTextureProfile(std::shared_ptr<TextureProfile> texture)
  {
    if (texture != nullptr)
    {
      if (texture->diffuse != nullptr)
      {
        if (!texture->diffuse->m_initialized)
          texture->diffuse->initialize();

        m_textures->diffuse = texture->diffuse;
      }

      if (texture->specular != nullptr)
      {
        if (!texture->specular->m_initialized)
          texture->specular->initialize();

        m_textures->specular = texture->specular;
      }

      if (texture->normal != nullptr)
      {
        if (!texture->normal->m_initialized)
          texture->normal->initialize();

        m_textures->normal = texture->normal;
      }

      if (texture->bump != nullptr)
      {
        if (!texture->bump->m_initialized)
          texture->bump->initialize();

        m_textures->bump = texture->bump;
      }

      if (texture->height != nullptr)
      {
        if (!texture->height->m_initialized)
          texture->height->initialize();

        m_textures->height = texture->height;
      }
    }
  }

  void GeometryNode::setMaterialProfile(const MaterialProfile &material)
  {
    m_material.ambient = material.ambient;
    m_material.diffuse = material.diffuse;
    m_material.specular = material.specular;
    m_material.shininess = material.shininess;
  }

  void GeometryNode::setDiffuseTexture(std::shared_ptr<Texture> diffuse)
  {
    if (diffuse != nullptr)
    {
      diffuse->initialize();
      m_textures->diffuse = diffuse;
    }
  }

  void GeometryNode::setSpecularTexture(std::shared_ptr<Texture> specular)
  {
    if (specular != nullptr)
    {
      specular->initialize();
      m_textures->specular = specular;
    }
  }

  void GeometryNode::setNormalTexture(std::shared_ptr<Texture> normal)
  {
    if (normal != nullptr)
    {
      normal->initialize();
      m_textures->normal = normal;
    }
  }

  void GeometryNode::setBumpTexture(std::shared_ptr<Texture> bump)
  {
    if (bump != nullptr)
    {
      bump->initialize();
      m_textures->bump = bump;
    }
  }

  void GeometryNode::setHeightTexture(std::shared_ptr<Texture> height)
  {
    if (height != nullptr)
    {
      height->initialize();
      m_textures->height = height;
    }
  }

  void GeometryNode::setModel(std::shared_ptr<Model> model)
  {
    if (model != nullptr)
    {
      if (!model->m_initialized)
        model->initialize();
    
      m_Model = model;
    }
    else
      m_Model = nullptr;
  }
}