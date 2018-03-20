--TEST--
CommonMark\Node fetch BulletList
--FILE--
<?php
$md = <<<MD
  * item
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\BulletList) {
	echo "OK";
}
?>
--EXPECT--
OK
