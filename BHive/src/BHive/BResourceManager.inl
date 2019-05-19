namespace BHive
{
	template<typename T>
	void BResourceManager::LoadAsset(String name, String loadPath)
	{
		std::unique_ptr<T> asset = std::make_unique<T>();
		asset->SetDisplayName(name);
		asset->SetFileName(name);
		asset->SetFilePath(loadPath);
		asset->Serialize();
		m_Assets.emplace(std::make_pair(name, std::move(asset)));
	}

	template<typename T>
	void BResourceManager::LoadResource(const String & name, const String & path)
	{
		std::unique_ptr<T> asset = std::make_unique<T>()
			asset->SetDisplayName(name);
		asset->SetFileName(name);
		asset->SetFilePath(path);
		asset->Serialize();
		m_Assets.emplace(std::make_pair(name, std::move(asset)));
	}
}