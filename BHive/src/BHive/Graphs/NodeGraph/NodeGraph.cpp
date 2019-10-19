#include "BHivePCH.h"
#include "NodeGraph.h"

namespace BHive
{
	void Edge::SetInput(Node& entry)
	{
		Input = &entry;
	}

	void Edge::SetOutput(Node& entry)
	{
		Output = &entry;
	}

	Node::Node()
		:mPath(""), mIsDirectory(true), Object()
	{

	}

	Node::Node(FString name, int numInputs, int numOutputs)
		:Node()
	{
		mNumInputs = numInputs;
		mNumOutputs = numOutputs;

		mInputEdges = std::vector<Edge*>(mNumInputs);
		mOutputEdges = std::vector<Edge*>(mNumOutputs);	
	}

	Node::~Node()
	{

	}

	void Node::AddInput(Edge& input, int index)
	{
		mInputEdges[index] = &input;
	}

	void Node::AddOutput(Edge& ouput, int index)
	{
		mOutputEdges[index] = &ouput;
	}

	void Node::RemoveInput(Edge& input, int index)
	{
		mInputEdges[index] = nullptr;
	}

	void Node::RemoveOutput(Edge& output, int index)
	{
		mOutputEdges[index] = nullptr;
	}

	bool Node::IsInputConnected(int index) const
	{
		return mInputEdges[index] != nullptr;
	}

	bool Node::IsOutputConnected(int index) const
	{
		return mOutputEdges[index] != nullptr;
	}

	/*void Node::OnSelection(bool selected)
	{
		if (selected)
		{
			NodeGraph::s_SelectedEntries.emplace_back(this);
		}
		else
		{
			auto entry = std::find(NodeGraph::s_SelectedEntries.begin(), NodeGraph::s_SelectedEntries.end(), this);
			NodeGraph::s_SelectedEntries.erase(entry);
		}

	}*/
	
	NodeGraph::NodeGraph(Node* root)
		:mRoot(root)
	{

	}

	NodeGraph::NodeGraph()
	{

	}

	void NodeGraph::Construct()
	{
		//Create Node Graph
	}

	void NodeGraph::SetRoot(std::unique_ptr <Node> root)
	{
		mRoot = root.get();
	}

	void NodeGraph::AddNode(std::unique_ptr <Node> node)
	{
		if (mRoot == nullptr) mRoot = node.get();

		mNodes.emplace(std::make_pair(node->GetDisplayName(), std::move(node)));
	}

	std::vector<Node*> NodeGraph::s_SelectedEntries;

}