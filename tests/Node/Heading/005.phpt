--TEST--
CommonMark\Node fetch Heading
--FILE--
<?php
$md = <<<MD
Heading
=======
MD;

$parser = new CommonMark\Parser();

$parser->parse($md);

$doc = $parser->finish();

if ($doc->firstChild instanceof CommonMark\Node\Heading) {
	echo "OK";
}
?>
--EXPECT--
OK
