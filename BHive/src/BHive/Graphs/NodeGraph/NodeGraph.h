#pragma once

#include "BHive/Object/Object.h"

namespace BHive
{	
	class NodeGraph;
	class Node;
	class Edge;

	class Edge 
	{
	public:
		Edge() {};

		void SetInput(Node& entry);
		void SetOutput(Node& entry);

		Node* GetInput() const { return Input; };
		Node* GetOutput() const {return Output;};

		//virtual void OnGUIRender() override;

	private:
		Node* Input;
		Node* Output;
	};

	class Node : public Object
	{
	public:
		Node();
		Node(FString name, int numInputs = 0, int numOutputs = 1);
		virtual ~Node();


		//virtual void OnGUIRender() override;

	public:
		FString mPath;
		bool mIsDirectory;

		int mNumInputs;
		int mNumOutputs;
	private:
		std::vector<Edge*> mInputEdges;
		std::vector<Edge*> mOutputEdges;

	public:
		void AddInput(Edge& input, int index);
		void AddOutput(Edge& ouput, int index);
		void RemoveInput(Edge& input, int index);
		void RemoveOutput(Edge& output, int index);

		bool IsInputConnected(int index) const;
		bool IsOutputConnected(int index) const;

		friend class NodeGraph;
	};

	class NodeGraph
	{
	public:
		NodeGraph();
		NodeGraph(Node* root);
		
	private:
		Node* mRoot;

		std::unordered_map<FName, std::unique_ptr<Node>> mNodes;//Store entries here
		std::vector<std::unique_ptr<Edge>> mEdges;

		static std::vector<Node*> s_SelectedEntries; //when removing doesn't delete <-- vector doesn't own entries

	public:
		virtual void Construct();

		//virtual void OnGUIRender() override;
	private:
		void SetRoot(std::unique_ptr <Node> root);
	public:
		void AddNode(std::unique_ptr <Node> node);

	private:
		friend class Node;
	};
}