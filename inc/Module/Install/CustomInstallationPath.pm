#line 1 "inc/Module/Install/CustomInstallationPath.pm - /Library/Perl/5.8.1/Module/Install/CustomInstallationPath.pm"
package Module::Install::CustomInstallationPath;

use strict;
use File::HomeDir;
use Config;

use vars qw( @ISA $VERSION );

use Module::Install::Base;
@ISA = qw( Module::Install::Base );

$VERSION = '0.10.3';

# ---------------------------------------------------------------------------

sub Check_Custom_Installation
{
  my $self = shift;

  # Module::Install says it requires perl 5.004
  $self->requires( perl => '5.004' );
  $self->include_deps('File::HomeDir',0);

  return if (grep {/^PREFIX=/} @ARGV) || (grep {/^INSTALLDIRS=/} @ARGV);

  my $install_location = $self->prompt(
    "Would you like to install this package into a location other than the\n" .
    "default Perl location (i.e. change the PREFIX)?" => 'n');

  if ($install_location eq 'y')
  {
    my $home = home();

    die "Your home directory could not be determined. Aborting."
      unless defined $home;

    print "\n","-"x78,"\n\n";

    my $prefix = $self->prompt(
      "What PREFIX should I use?\n=>" => $home);

    push @ARGV,"PREFIX=$prefix";
  }
}

1;

# ---------------------------------------------------------------------------

#line 106

