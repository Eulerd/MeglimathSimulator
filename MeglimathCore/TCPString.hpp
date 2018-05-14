# pragma once
# include <Siv3D.hpp>

namespace asc
{
	using namespace s3d;

	/// <summary>
	/// ������𑗎�M�\�� TCPClient, TCPServer
	/// </summary>
	/// <remarks>
	/// ����M�� UTF-8 �ōs���܂��B
	/// </remarks>
	template<class Socket>
	class TCPString : public Socket
	{
	public:

		/// <summary>
		/// 1 �����ǂݍ��݂܂��B
		/// </summary>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������͐����������܂���B
		/// </remarks>
		bool readChar(char32& to)
		{
			std::string buffer;

			buffer.resize(1);

			if (!lookahead(buffer[0]))
				return false;

			skip(sizeof(std::string::value_type));
			to = Unicode::FromUTF8(std::move(buffer))[0];
			
			return true;
		}

		/// <summary>
		/// ���������w�肵�ĕ������ǂݍ��݂܂��B
		/// </summary>
		/// <param name="length">
		/// �ǂݍ��ޕ�����
		/// </param>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������͐����������܂���B
		/// </remarks>
		bool readString(size_t length, String& to)
		{
			std::string buffer;

			buffer.resize(length);

			if (!lookahead(&buffer[0], buffer.size()))
				return false;

			skip(sizeof(std::string::value_type) * buffer.size());
			to = Unicode::FromUTF8(std::move(buffer));

			return true;
		}

		/// <summary>
		/// 1 �s�ǂݍ��݂܂��B
		/// </summary>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������������܂��B
		/// </remarks>
		/// <remarks>
		/// ���s�R�[�h�� LF ���g�p���܂��B
		/// </remarks>
		bool readLine(String& to)
		{
			return readUntil('\n', to);
		}

		/// <summary>
		/// �w�肵������������܂œǂݍ��݂܂��B
		/// </summary>
		/// <param name="end">
		/// �w�肷�镶��
		/// </param>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������������܂��B
		/// </remarks>
		bool readUntil(char end, String& to)
		{
			std::string buffer;

			buffer.resize(available());

			if (!lookahead(&buffer[0], buffer.size()))
				return false;

			const auto pos = buffer.find(end);

			if (pos == buffer.npos)
				return false;

			buffer.resize(pos + 1);

			skip(sizeof(std::string::value_type) * buffer.size());
			to = Unicode::FromUTF8(std::move(buffer));

			return true;
		}

		/// <summary>
		/// �w�肵�������񂪗���܂œǂݍ��݂܂��B
		/// </summary>
		/// <param name="end">
		/// �w�肷�镶����
		/// </param>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������������܂��B
		/// </remarks>
		bool readUntil(const String& end, String& to)
		{
			std::string buffer;

			buffer.resize(available());

			if (!lookahead(&buffer[0], buffer.size()))
				return false;

			const auto str = end.toUTF8();
			const auto pos = buffer.find(str);

			if (pos == buffer.npos)
				return false;

			buffer.resize(pos + str.size());

			skip(sizeof(std::string::value_type) * buffer.size());
			to = Unicode::FromUTF8(std::move(buffer));

			return true;
		}

		/// <summary>
		/// �������\�Ȍ���ǂݍ��݂܂��B
		/// </summary>
		/// <param name="to">
		/// �ǂݍ��ݐ�
		/// </param>
		/// <returns>
		/// �ǂݍ��݂ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������������܂��B
		/// </remarks>
		bool readAll(String& to)
		{
			std::string buffer;

			buffer.resize(available());

			if (!lookahead(&buffer[0], buffer.size()))
				return false;

			skip(sizeof(std::string::value_type) * buffer.size());
			to = Unicode::FromUTF8(std::move(buffer));

			return true;
		}

		/// <summary>
		/// ������𑗐M���܂��B
		/// </summary>
		/// <param name="data">
		/// ���M���镶����
		/// </param>
		/// <returns>
		/// ���M�ɐ�������� true
		/// </returns>
		/// <remarks>
		/// ���{��Ȃǂ� 1 �o�C�g�ł͂Ȃ������������܂��B
		/// </remarks>
		bool sendString(const String& data);

		bool sendString(const String& data, const Optional<SessionID>& id);
	};

	template<>
	bool TCPString<TCPServer>::sendString(const String& data, const Optional<SessionID>& id)
	{
		const auto str = data.toUTF8();

		return send(str.data(), str.length(), id);
	}

	template<>
	bool TCPString<TCPClient>::sendString(const String& data)
	{
		const auto str = data.toUTF8();

		return send(str.data(), str.length());
	}

	using TCPStringClient = TCPString<TCPClient>;
	using TCPStringServer = TCPString<TCPServer>;
}