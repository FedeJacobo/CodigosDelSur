using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using AutoMapper;
using IMMRequest.BusinessLogic.Interfaces;
using IMMRequest.Entities;
using IMMRequest.WebApi.Mapper;
using IMMRequest.WebApi.Models;
using Microsoft.AspNetCore.Http;
using Microsoft.AspNetCore.Mvc;

namespace IMMRequest.WebApi.Controllers
{
    [Route("api/[controller]")]
    [ApiController]
    public class AreaController : ControllerBase
    {
        private IAreaLogic areaLogic;
        private IMapper mapper;
        public AreaController(IAreaLogic areaLogic, IWebApiMapper apiMapper)
        {
            this.mapper = apiMapper.Configure();
            this.areaLogic = areaLogic;
        }

        // GET: api/Area
        [HttpGet]
        public ActionResult Get()
        {
            IEnumerable<AreaEntity> areas;
            try
            {
                areas = areaLogic.GetAll();
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            var areasOut = mapper.Map<IEnumerable<AreaEntity>, IEnumerable<AreaModelOut>>(areas);
            return this.Ok(areasOut);
        }

        // GET: api/Area/name
        [HttpGet("{name}")]
        public ActionResult Get(string name)
        {
            AreaEntity area;
            try
            {
                area = areaLogic.GetByName(name);
            }
            catch (ArgumentException ex)
            {
                return BadRequest(ex.Message);
            }
            catch (Exception ex)
            {
                return BadRequest(ex.Message);
            }
            var areaOut = mapper.Map<AreaEntity, AreaModelOut>(area);
            return this.Ok(areaOut);
        }

        // POST: api/Area
        [HttpPost]
        public IActionResult Post([FromBody] AreaModelIn areaModelIn)
        {
            if (ModelState.IsValid)
            {
                try
                {
                    var area = mapper.Map<AreaModelIn, AreaEntity>(areaModelIn);
                    var id = areaLogic.Add(area);
                    var addedArea = areaLogic.GetByName(area.Name);
                    var addedAreaOut = mapper.Map<AreaEntity, AreaModelOut>(addedArea);
                    return Created("Posted succesfully", addedAreaOut);
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
    }
}
