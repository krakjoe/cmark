--TEST--
CommonMark\Node fetch Link
--FILE--
<?php
$md = <<<MD
[link](/url "title")
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

$root = $doc->getFirstChild();

$img = $root->getFirstChild();

if ($img instanceof CommonMark\Node\Media\Link) {
	echo "OK";
}
?>
--EXPECT--
OK
