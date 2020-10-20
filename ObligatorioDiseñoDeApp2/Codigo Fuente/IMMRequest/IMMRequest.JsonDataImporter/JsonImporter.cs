using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using Newtonsoft.Json.Linq;
using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace IMMRequest.JsonDataImporter
{
    public class JsonImporter : IGenericImporter
    {
        public string GetName()
        {
            return "Json";
        }

        public ICollection<string> GetTypeParameters()
        {
            return new List<string>() { "Path" };
        }

        public ICollection<AreaEntity> GetAreas(ICollection<Parameter> parameters)
        {
            try
            {
                var pathJsonFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                var jsonText = File.ReadAllText(pathJsonFile);
                JObject dataIn = JObject.Parse(jsonText);
                IList<JToken> results = dataIn["AreaEntity"].Children().ToList();

                var result = new List<AreaEntity>();
                foreach (JToken areaIn in results)
                {
                    AreaEntity newArea = new AreaEntity();
                    newArea.Name = areaIn.ToObject<AreaEntity>().Name;
                    result.Add(newArea);
                }

                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path invalido");
            }            
        }

        public ICollection<TopicEntity> GetTopics(ICollection<Parameter> parameters)
        {
            try
            {
                var pathJsonFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                var jsonText = File.ReadAllText(pathJsonFile);
                JObject dataIn = JObject.Parse(jsonText);
                IList<JToken> results = dataIn["TopicEntity"].Children().ToList();

                var result = new List<TopicEntity>();
                foreach (JToken topicIn in results)
                {
                    TopicEntity newTopic = new TopicEntity();
                    newTopic.Name = topicIn.ToObject<TopicEntity>().Name;
                    newTopic.AreaEntityId = topicIn.ToObject<TopicEntity>().AreaEntityId;
                    result.Add(newTopic);
                }

                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path invalido");
            }
        }

        public ICollection<TypeReqEntity> GetTypeReqs(ICollection<Parameter> parameters)
        {
            try
            {
                var pathJsonFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                var jsonText = File.ReadAllText(pathJsonFile);
                JObject dataIn = JObject.Parse(jsonText);
                IList<JToken> results = dataIn["TypeReqEntity"].Children().ToList();

                var result = new List<TypeReqEntity>();
                foreach (JToken typeReqIn in results)
                {
                    TypeReqEntity newType = new TypeReqEntity();
                    newType.Name = typeReqIn.ToObject<TypeReqEntity>().Name;
                    newType.TopicEntityId = typeReqIn.ToObject<TypeReqEntity>().TopicEntityId;
                    result.Add(newType);
                }

                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path invalido");
            }
        }
    }
}