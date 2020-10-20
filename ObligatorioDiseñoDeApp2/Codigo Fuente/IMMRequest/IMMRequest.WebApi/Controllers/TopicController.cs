using AutoMapper;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Authorization;
using Microsoft.AspNetCore.Mvc;
using System;
using System.Collections.Generic;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class TopicController : ControllerBase
    {
        private ITopicLogic topicLogic;
        private IMapper mapper;

        public TopicController(ITopicLogic topicLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.topicLogic = topicLogic;
        }

        [HttpGet]
        public ActionResult Get()
        {
            IEnumerable<TopicEntity> topics;
            try
            {
                topics = topicLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var topicsOut = mapper.Map<IEnumerable<TopicEntity>, IEnumerable<TopicModelOut>>(topics);
            return this.Ok(topicsOut);
        }

        [HttpPost]
        public IActionResult Post([FromBody] TopicModelIn topicIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var topic = mapper.Map<TopicModelIn, TopicEntity>(topicIn);
                    var id = topicLogic.Add(topic);
                    var addedTopic = topicLogic.GetByName(topic.Name);
                    var addedTopicOut = mapper.Map<TopicEntity, TopicModelOut>(addedTopic);
                    return Created("Posted succesfully", addedTopicOut);
                }
                catch (ArgumentException ex)
                {
                    return BadRequest(ex.Message);
                }
                catch (Exception ex)
                {
                    return BadRequest(ex.Message);
                }
            }
            else
            {
                return BadRequest(ModelState);
            }
        }

        [HttpGet("{name}")]
        [AllowAnonymous]
        public ActionResult Get(string name)
        {
            TopicEntity topic;
            try
            {
                topic = topicLogic.GetByName(name);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var topicOut = mapper.Map<TopicEntity, TopicModelOut>(topic);
            return this.Ok(topicOut);
        }
    }
}