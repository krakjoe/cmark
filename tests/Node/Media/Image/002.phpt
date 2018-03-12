--TEST--
CommonMark\Node fetch Image
--FILE--
<?php
$md = <<<MD
![foo](bar.jpg)
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$root = $doc->getFirstChild();

$img = $root->getFirstChild();

if ($img instanceof CommonMark\Node\Media\Image) {
	echo "OK";
}
?>
--EXPECT--
OK
