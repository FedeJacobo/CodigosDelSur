using IMMRequest.Entities;
using IMMRequest.IDataImporter;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Xml;

namespace IMMRequest.XmlDataImporter
{
    public class XmlImporter : IGenericImporter
    {
        public string GetName()
        {
            return "Xml";
        }
        public ICollection<string> GetTypeParameters()
        {
            return new List<string>() { "Path" };
        }

        public ICollection<AreaEntity> GetAreas(ICollection<Parameter> parameters)
        {
            try
            {
                var pathXmlFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                XmlDocument doc = new XmlDocument();
                doc.Load(pathXmlFile);

                var result = new List<AreaEntity>();

                XmlNode node = doc.DocumentElement.SelectSingleNode("Areas");
                foreach (XmlNode areaNode in node.ChildNodes)
                {
                    AreaEntity newArea = new AreaEntity();
                    foreach (XmlNode dataNode in areaNode.ChildNodes)
                    {
                        newArea.Name = dataNode.InnerText;
                    }
                    result.Add(newArea);
                }
                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path Invalido");
            }
        }

        public ICollection<TopicEntity> GetTopics(ICollection<Parameter> parameters)
        {
            try
            {
                var pathXmlFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                XmlDocument doc = new XmlDocument();
                doc.Load(pathXmlFile);

                var result = new List<TopicEntity>();

                XmlNode node = doc.DocumentElement.SelectSingleNode("Topics");
                foreach (XmlNode topicNode in node.ChildNodes)
                {
                    TopicEntity newTopic = new TopicEntity();
                    foreach (XmlNode dataNode in topicNode.ChildNodes)
                    {
                        if (dataNode.Name.Equals("Name"))
                        {
                            newTopic.Name = dataNode.InnerText;
                        }
                        else if (dataNode.Name.Equals("AreaEntityId"))
                        {
                            int id = 0;
                            Int32.TryParse(dataNode.InnerText, out id);
                            newTopic.AreaEntityId = id;
                        }
                        
                    }
                    result.Add(newTopic);
                }
                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path Invalido");
            }
        }

        public ICollection<TypeReqEntity> GetTypeReqs(ICollection<Parameter> parameters)
        {
            try
            {
                var pathXmlFile = parameters.OfType<Parameter>().FirstOrDefault().Value;
                XmlDocument doc = new XmlDocument();
                doc.Load(pathXmlFile);

                var result = new List<TypeReqEntity>();

                XmlNode node = doc.DocumentElement.SelectSingleNode("Types");
                foreach (XmlNode typeNode in node.ChildNodes)
                {
                    TypeReqEntity newType = new TypeReqEntity();
                    foreach (XmlNode dataNode in typeNode.ChildNodes)
                    {
                        if (dataNode.Name.Equals("Name"))
                        {
                            newType.Name = dataNode.InnerText;
                        }
                        else if (dataNode.Name.Equals("TopicEntityId"))
                        {
                            int id = 0;
                            Int32.TryParse(dataNode.InnerText, out id);
                            newType.TopicEntityId = id;
                        }

                    }
                    result.Add(newType);
                }
                return result;
            }
            catch (ArgumentException)
            {
                throw new ArgumentException("Path Invalido");
            }
        }
    }
}
