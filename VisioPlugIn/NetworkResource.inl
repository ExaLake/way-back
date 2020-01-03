// NetworkResource.inl
// Inline method definitions.

void CNetworkResource::SetDisplayName(LPTSTR val)
{
	// Ideally we would clean up the name
	// at this point. For example, computers
	// come in as \\<computer name> and shares
	// as \\<computer name>\<share>. For the sake
	// of clarity I'll leave this as an exercise.
	m_DisplayName = val;
}

CString CNetworkResource::GetDisplayName()
{
	return(m_DisplayName);
}

void CNetworkResource::SetDisplayType(DWORD val)
{
	m_DisplayType = val;
}

DWORD CNetworkResource::GetDisplayType()
{
	return(m_DisplayType);
}

void CNetworkResource::SetType(DWORD val)
{
	m_Type = val;
}

DWORD CNetworkResource::GetType()
{
	return(m_Type);
}

CVisioShape& CNetworkResource::GetShape()
{
	return(m_Shape);
}
