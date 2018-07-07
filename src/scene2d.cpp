#include <include/scene2d.h>

Scene2d::Scene2d() :
    sinfo("", ""),
    objid(0)
{
    m_objs.clear();
    toDelete.clear();
}

void Scene2d::start(AudioManager *mgr)
{
    mgr->stopMusic();
    if(!sinfo.bg_track.empty())
    {
        mgr->playMusic(sinfo.bg_track, true);
    }
}

void Scene2d::addActor(vec2 pos, vec2 dim, vec2 rdim, map<unistring, unistring> trigger, unistring name, unistring type, unistring texture, unistring anim_idle)
{
    Actor2d actor;

    actor.setPos(pos);
    actor.setDim(dim);
    actor.setRealDim(rdim);
    actor.setName(name);
    actor.setType(type);
    actor.setTex(texture);

    actor.trigger = trigger;
    actor.idle_anim = anim_idle;
    actor.curAnim = actor.idle_anim;

    m_objs[name] = actor;
}

void Scene2d::addToQueue(unistring object)
{
    toDelete.push_back(object);
}

void Scene2d::doOperations()
{
    for(const auto &op : toDelete)
    {
        m_objs.erase(op);
    }
    toDelete.clear();
}

void Scene2d::addActor(AppConfig &conf, vec2 pos, unistring model_id, unistring parent)
{
    Actor2d actor;
    actor = conf.app_models[model_id];

    actor.setName( model_id+"_"+ to_string(objid) );
    actor.parent = parent;
    objid++;
    actor.setPos(pos);

    m_objs.insert( std::pair<unistring, Actor2d>( actor.getName(), actor ) );
    Logger::log("Scene2d", "Added model '"+model_id+"' on scene as '"+actor.getName()+"'.");
}

SDL_Rect &Scene2d::getRect(unistring name)
{
    return m_objs[name].rect;
}

void Scene2d::clear()
{
    for(const auto &it : m_objs)
        addToQueue(it.first);
    objid = 0;
}
