Name:           lamia-libs
Version:        0.3.0
Release:        1%{?dist}
Summary:        Lamia Language Libraries

License:        MIT
URL:            https://github.com/The-Medusa-Initiative-Project/Lamia-Libs
Source0:        lamia-v0.3.0-source.tar.gz

BuildRequires:  gcc-c++ >= 9
BuildRequires:  make
Requires:       glibc >= 2.17

%description
Revolutionary programming language libraries featuring 3D emotions,
social protocols, and native manufacturing integration.

%prep
%autosetup -n lamia-v0.3.0

%build
make all

%install
mkdir -p %{buildroot}/usr/lib/lamia
mkdir -p %{buildroot}/usr/include/lamia
cp lib/*.so %{buildroot}/usr/lib/lamia/
cp Lamia-Libs/lib/*.so %{buildroot}/usr/lib/lamia/
cp Lamia-Libs/include/*.hpp %{buildroot}/usr/include/lamia/

%files
/usr/lib/lamia/*.so
/usr/include/lamia/*.hpp

%changelog
* Thu Jan 16 2025 The Medusa Project - 0.3.0-1
- Revolutionary release with 20+ libraries
